#include "app_radio.h"

#include "rail.h"
#include "sl_rail.h"
#include "sl_rail_types.h"
#include "sl_rail_ieee802154.h"

#include "em_cmu.h"
#include "em_prs.h"
#include "em_core.h"

#include "sl_status.h"
#include "stdio.h"
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define TX_FIFO_BYTES 256

#define MAX_PACKET_LEN       128
#define RX_PACKET_QUEUE_SIZE 10

typedef struct {
  uint16_t length;
  uint8_t  data[MAX_PACKET_LEN];
} rx_packet_t;

static void radio_event_handler(sl_rail_handle_t rail_handle,
                                sl_rail_events_t events);

static SL_RAIL_DECLARE_FIFO_BUFFER(aligned_tx_fifo, TX_FIFO_BYTES);

sl_rail_handle_t greenPowerHandle_g = SL_RAIL_EFR32_HANDLE;

sl_rail_config_t railCfg;

/* Kept across the legal image's reset path for debugger inspection. */
volatile RAIL_AssertErrorCodes_t app_radio_last_assert_error
  __attribute__((section(".noinit")));
volatile uintptr_t app_radio_last_assert_handle
  __attribute__((section(".noinit")));

// Circular buffer for 10 packets
static rx_packet_t app_rx_queue[RX_PACKET_QUEUE_SIZE];
static volatile uint8_t rx_head = 0; // Write index
static volatile uint8_t rx_tail = 0; // Read index
static volatile uint8_t rx_count = 0; // Number of packets stored

/*******************************************************************************
 * Start RX on Channel
 ******************************************************************************/
sl_rail_status_t app_radio_start_rx_channel(uint8_t channel_a)
{
  return sl_rail_start_rx(greenPowerHandle_g, channel_a, NULL);
}

/*******************************************************************************
 * Process Action: Pop packet from queue
 * Call this from your application loop/process action.
 * Returns true if a packet was retrieved, false if buffer is empty.
 ******************************************************************************/
bool app_radio_get_packet(uint8_t *dest_buffer, uint16_t *p_length, uint16_t max_buf_size)
{
  if (dest_buffer == NULL || p_length == NULL) {
    return false;
  }

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();
  if (rx_count == 0U) {
    CORE_EXIT_ATOMIC();
    return false;
  }

  // Copy oldest available packet out
  uint16_t len = app_rx_queue[rx_tail].length;
  if (len > max_buf_size) {
    len = max_buf_size;
  }
  memcpy(dest_buffer, app_rx_queue[rx_tail].data, len);
  *p_length = len;

  // Advance read pointer
  rx_tail = (rx_tail + 1) % RX_PACKET_QUEUE_SIZE;
  rx_count--;
  CORE_EXIT_ATOMIC();

  return true;
}

/*******************************************************************************
 * Transmit fixed payload demo packet on Channel 19
 ******************************************************************************/
sl_rail_status_t app_radio_send_demo_packet(uint8_t channel_a)
{
  static const uint8_t demo_payload[] = {
    0x0B,                                     // Length byte (for 802.15.4 PHR / packet format)
    0x01, 0x08,                               // Frame Control (e.g. Data frame)
    0x01,                                     // Sequence number
    0xFF, 0xFF,                               // Destination PAN ID (Broadcast)
    0xFF, 0xFF,                               // Destination Address (Broadcast)
    0xDE, 0xAD, 0xBE, 0xEF                    // Payload data
  };

  // Write payload to the TX FIFO with reset = true
  sl_rail_write_tx_fifo(greenPowerHandle_g, demo_payload, sizeof(demo_payload), true);

  // Trigger packet transmission on channel 19
  return sl_rail_start_tx(greenPowerHandle_g, channel_a, SL_RAIL_TX_OPTIONS_DEFAULT, NULL);
}

sl_rail_status_t app_radio_init(void)
{
  sl_rail_status_t initStatus;

  railCfg.events_callback = &radio_event_handler;
  railCfg.rx_packet_queue_entries = sl_rail_builtin_rx_packet_queue_entries;
  railCfg.rx_fifo_bytes = sl_rail_builtin_rx_fifo_bytes;
  railCfg.p_rx_packet_queue = sl_rail_builtin_rx_packet_queue_ptr;
  railCfg.p_rx_fifo_buffer = sl_rail_builtin_rx_fifo_ptr;
  railCfg.tx_fifo_bytes = TX_FIFO_BYTES;
  railCfg.tx_fifo_init_bytes = 0U;
  railCfg.p_tx_fifo_buffer = aligned_tx_fifo;

  // -------------------------------------------------------------------------
  // Step 2: Initialize RAIL
  // -------------------------------------------------------------------------
  initStatus = sl_rail_init(&greenPowerHandle_g, &railCfg, NULL);
  if (initStatus != SL_RAIL_STATUS_NO_ERROR)
  {
    printf("RAIL init failed: sl_rail_init (0x%08lx)\r\n", (unsigned long)initStatus);
    return initStatus;
  }

  // // -------------------------------------------------------------------------
  // // Step 3: PA post-init (must be after sl_rail_init, before TX)
  // // Establishes default PA voltage and ramp time.
  // // Use SL_RAIL_TX_PA_MODE_2P4_GHZ for 2.4 GHz 802.15.4
  // // -------------------------------------------------------------------------
  // initStatus = sl_rail_util_pa_post_init(greenPowerHandle_g, SL_RAIL_TX_PA_MODE_2P4_GHZ);
  // if (initStatus != SL_RAIL_STATUS_NO_ERROR)
  // {
  //   while(1);
  // }

  // // -------------------------------------------------------------------------
  // // Step 4: Configure data (packet mode)
  // // NOTE: sl_rail_config_tx_data / sl_rail_config_rx_data are the RAIL 3
  // // equivalents of RAIL_ConfigData. Adjust if your SDK exposes them separately.
  // // -------------------------------------------------------------------------
  // initStatus = sl_rail_config_data(greenPowerHandle_g, &data_config);
  // if (initStatus != SL_RAIL_STATUS_NO_ERROR)
  // {
  //   while(1);
  // }

  // -------------------------------------------------------------------------
  // Step 5: Configure calibration
  // Do NOT leave this commented out in production code.
  // Handle SL_RAIL_EVENT_CAL_NEEDED in your event callback as well.
  // -------------------------------------------------------------------------
  initStatus = sl_rail_config_cal(greenPowerHandle_g, SL_RAIL_CAL_ALL);
  if (initStatus != SL_RAIL_STATUS_NO_ERROR)
  {
    printf("RAIL init failed: sl_rail_config_cal (0x%08lx)\r\n", (unsigned long)initStatus);
    return initStatus;
  }

  // -------------------------------------------------------------------------
  // Step 6: Configure 2.4 GHz 802.15.4 radio
  // This replaces RAIL_ConfigChannels() — do NOT call both.
  // -------------------------------------------------------------------------
  initStatus = sl_rail_ieee802154_config_2p4_ghz_radio(greenPowerHandle_g);
  if (initStatus != SL_RAIL_STATUS_NO_ERROR)
  {
    printf("RAIL init failed: 802.15.4 radio config (0x%08lx)\r\n", (unsigned long)initStatus);
    return initStatus;
  }

  // // -------------------------------------------------------------------------
  // // Step 7: Initialize IEEE 802.15.4 protocol
  // // This internally sets RX/TX transitions and auto-ack — do NOT override
  // // them with sl_rail_set_rx_transitions / sl_rail_set_tx_transitions after
  // // this call unless you have a specific reason to.
  // // -------------------------------------------------------------------------
  // initStatus = sl_rail_ieee802154_init(greenPowerHandle_g, &rail154Config);
  // if (initStatus != SL_RAIL_STATUS_NO_ERROR)
  // {
  //   while(1);
  // }

  // -------------------------------------------------------------------------
  // Step 8: Configure events
  // -------------------------------------------------------------------------
  initStatus = sl_rail_config_events(greenPowerHandle_g,
                                     SL_RAIL_EVENTS_ALL,
                                     SL_RAIL_EVENTS_ALL);
  if (initStatus != SL_RAIL_STATUS_NO_ERROR)
  {
    printf("RAIL init failed: sl_rail_config_events (0x%08lx)\r\n", (unsigned long)initStatus);
    return initStatus;
  }

  // -------------------------------------------------------------------------
  // Step 9: Configure RX options
  // -------------------------------------------------------------------------
  initStatus = sl_rail_config_rx_options(greenPowerHandle_g,
                                         SL_RAIL_RX_OPTION_IGNORE_CRC_ERRORS,
                                         SL_RAIL_RX_OPTION_IGNORE_CRC_ERRORS);
  if (initStatus != SL_RAIL_STATUS_NO_ERROR)
  {
    printf("RAIL init failed: sl_rail_config_rx_options (0x%08lx)\r\n", (unsigned long)initStatus);
    return initStatus;
  }

  // -------------------------------------------------------------------------
  // Step 10: Setup TX FIFO
  // -------------------------------------------------------------------------
  initStatus = sl_rail_set_tx_fifo(greenPowerHandle_g,
                                   aligned_tx_fifo,
                                   TX_FIFO_BYTES,
                                   0,
                                   0);
  if (initStatus != SL_RAIL_STATUS_NO_ERROR)
  {
    printf("RAIL init failed: sl_rail_set_tx_fifo (0x%08lx)\r\n", (unsigned long)initStatus);
    return initStatus;
  }

  return SL_RAIL_STATUS_NO_ERROR;

  // // -------------------------------------------------------------------------
  // // Step 11: Set TX power in dBm
  // // -------------------------------------------------------------------------
  // initStatus = sl_rail_set_tx_power_dbm(greenPowerHandle_g, txPower);
  // if (initStatus != SL_RAIL_STATUS_NO_ERROR)
  // {
  //   while(1);
  // }

//   // -------------------------------------------------------------------------
//   // Step 12: Configure sleep / timer sync
//   // -------------------------------------------------------------------------
//   CMU_ClockEnable(cmuClock_PRS, true);

//   sl_rail_timer_sync_config_t syncConfig = SL_RAIL_TIMER_SYNC_DEFAULT;
//   syncConfig.prs_channel = PRS_GetFreeChannel(prsTypeAsync);

//   initStatus = sl_rail_config_sleep(greenPowerHandle_g, &syncConfig);
//   if (initStatus != SL_RAIL_STATUS_NO_ERROR)
//   {
//     while(1);
//   }

//   // -------------------------------------------------------------------------
//   // Step 13: CCA configuration (optional)
//   // -------------------------------------------------------------------------
// #if CCA_ENABLE
//   csmaConfig.ccaThreshold = CCA_THRESHOLD_DBM;

// #if SL_RAIL_IEEE802154_SUPPORTS_SIGNAL_IDENTIFIER
//   if (sl_rail_ieee802154_supports_signal_identifier(greenPowerHandle_g))
//   {
//     initStatus = sl_rail_ieee802154_config_cca_mode(greenPowerHandle_g,
//                                                     SL_RAIL_IEEE802154_CCA_MODE_RSSI);
//     if (initStatus != SL_RAIL_STATUS_NO_ERROR)
//     {
//       while(1);
//     }
//   }
// #endif
// #endif // CCA_ENABLE

//   // -------------------------------------------------------------------------
//   // Step 14: PTI configuration (optional)
//   // -------------------------------------------------------------------------
// #if PTI_ENABLE
//   initStatus = sl_rail_config_pti(greenPowerHandle_g, &railPtiConfig);
//   if (initStatus != SL_RAIL_STATUS_NO_ERROR)
//   {
//     while(1);
//   }

//   // Capture return value and check it
//   initStatus = sl_rail_set_pti_protocol(greenPowerHandle_g,
//                                         SL_RAIL_PTI_PROTOCOL_ZIGBEE);
//   if (initStatus != SL_RAIL_STATUS_NO_ERROR)
//   {
//     while(1);
//   }
// #endif // PTI_ENABLE

//   // -------------------------------------------------------------------------
//   // Step 15: PRS radio debug outputs (optional)
//   // -------------------------------------------------------------------------
// #if RADIO_PRS_OUT
//   CMU_ClockEnable(cmuClock_GPIO, true);
//   // cmuClock_PRS already enabled above — no need to repeat

//   radioPrsSyncSentChannel = PRS_GetFreeChannel(prsTypeAsync);
//   PRS_SourceAsyncSignalSet(radioPrsSyncSentChannel,
//                            PRS_ASYNC_CH_CTRL_SOURCESEL_MODEMH,
//                            PRS_ASYNC_CH_CTRL_SIGSEL_MODEMHSYNCSENT);
//   GPIO_PinModeSet(RADIOPRS_SYNCSENT_GPIO_PORT, RADIOPRS_SYNCSENT_GPIO_PIN,
//                   gpioModePushPull, 1);
//   PRS_PinOutput(radioPrsSyncSentChannel, prsTypeAsync,
//                 RADIOPRS_SYNCSENT_GPIO_PORT, RADIOPRS_SYNCSENT_GPIO_PIN);

//   radioPrsFrameDetChannel = PRS_GetFreeChannel(prsTypeAsync);
//   PRS_SourceAsyncSignalSet(radioPrsFrameDetChannel,
//                            PRS_ASYNC_CH_CTRL_SOURCESEL_MODEML,
//                            PRS_ASYNC_CH_CTRL_SIGSEL_MODEMLFRAMEDET);
//   GPIO_PinModeSet(RADIOPRS_FRAMEDET_GPIO_PORT, RADIOPRS_FRAMEDET_GPIO_PIN,
//                   gpioModePushPull, 1);
//   PRS_PinOutput(radioPrsFrameDetChannel, prsTypeAsync,
//                 RADIOPRS_FRAMEDET_GPIO_PORT, RADIOPRS_FRAMEDET_GPIO_PIN);
// #endif // RADIO_PRS_OUT

}


static void radio_event_handler(sl_rail_handle_t rail_handle,
                                sl_rail_events_t events)
{
  if (events & SL_RAIL_EVENT_RX_PACKET_RECEIVED) {
    sl_rail_rx_packet_info_t packet_info;
    sl_rail_rx_packet_handle_t packet_handle;

    // Retrieve information on the received packet
    packet_handle = sl_rail_get_rx_packet_info(rail_handle,
                                               SL_RAIL_RX_PACKET_HANDLE_NEWEST,
                                               &packet_info);

    if (packet_handle != SL_RAIL_RX_PACKET_HANDLE_INVALID) {
      if (packet_info.packet_bytes <= MAX_PACKET_LEN) {
        CORE_DECLARE_IRQ_STATE;
        CORE_ENTER_ATOMIC();

        // Overwrite oldest if queue is full (data loss acceptable).
        if (rx_count == RX_PACKET_QUEUE_SIZE) {
          rx_tail = (rx_tail + 1) % RX_PACKET_QUEUE_SIZE;
          rx_count--;
        }

        // Copy the packet data into the application circular queue
        sl_rail_copy_rx_packet(rail_handle, app_rx_queue[rx_head].data, &packet_info);
        app_rx_queue[rx_head].length = packet_info.packet_bytes;

        rx_head = (rx_head + 1) % RX_PACKET_QUEUE_SIZE;
        rx_count++;

        CORE_EXIT_ATOMIC();
      }

      // Free packet handle in the RAIL FIFO/queue
      sl_rail_release_rx_packet(rail_handle, packet_handle);
    }
  }

  if (events & SL_RAIL_EVENT_TX_PACKET_SENT) {
    // Packet transmitted successfully
  }
}


void RAILCb_AssertFailed(RAIL_Handle_t railHandle, RAIL_AssertErrorCodes_t errorCode)
{
  app_radio_last_assert_handle = (uintptr_t)railHandle;
  app_radio_last_assert_error = errorCode;
  NVIC_SystemReset();
  for (;;) {
    // System reset should not return.
  }
}
