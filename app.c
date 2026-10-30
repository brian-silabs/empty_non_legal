/***************************************************************************//**
 * @file
 * @brief Callable side of the fixed-address split PoC.
 ******************************************************************************/

#include "../empty/split_interface.h"

#include <stdbool.h>
#include "radio_ccm.h"
#include "sli_protocol_crypto.h"
#include "app_radio.h"
#include "em_device.h"

extern const uint32_t __VECTOR_TABLE[];

#define DEMO_RADIO_CHANNEL 19U

static uint32_t process_count;
static bool initialized;

typedef struct {
  const uint32_t *source;
  uint32_t *destination;
  uint32_t word_count;
} split_copy_table_entry_t;

typedef struct {
  uint32_t *destination;
  uint32_t word_count;
} split_zero_table_entry_t;

extern const split_copy_table_entry_t __split_copy_table_start__[];
extern const split_copy_table_entry_t __split_copy_table_end__[];
extern const split_zero_table_entry_t __split_zero_table_start__[];
extern const split_zero_table_entry_t __split_zero_table_end__[];

static void initialize_non_legal_ram(void)
{
  for (const split_copy_table_entry_t *entry = __split_copy_table_start__;
       entry < __split_copy_table_end__;
       ++entry) {
    for (uint32_t i = 0U; i < entry->word_count; ++i) {
      entry->destination[i] = entry->source[i];
    }
  }

  for (const split_zero_table_entry_t *entry = __split_zero_table_start__;
       entry < __split_zero_table_end__;
       ++entry) {
    for (uint32_t i = 0U; i < entry->word_count; ++i) {
      entry->destination[i] = 0U;
    }
  }
}

/* Reset_Handler is never entered by the host. Initialize this image's RAM
 * from its linker tables before touching module/SDK globals. */
static sl_status_t non_legal_init(void)
{
  initialize_non_legal_ram();

  sl_rail_status_t radio_status = app_radio_init();
  if (radio_status != SL_RAIL_STATUS_NO_ERROR) {
    return SL_STATUS_FAIL;
  }


  sl_status_t status = sli_protocol_crypto_init();
  if (status != SL_STATUS_OK) { return status; }
  /* Seed before the legal SE worker starts: SDK masking uses SE entropy. */
  sli_aes_seed_mask();

  radio_status = app_radio_start_rx_channel(DEMO_RADIO_CHANNEL);
  if (radio_status != SL_RAIL_STATUS_NO_ERROR) {
    return SL_STATUS_FAIL;
  }

  process_count = 0U;
  initialized = true;
  return SL_STATUS_OK;
}

static uint32_t non_legal_process_action(void)
{
  if (initialized) {
    process_count++;
    app_radio_process_received_packets();
    // 1. Transmit the demo packet (called every second)
    sl_rail_status_t tx_status = app_radio_send_demo_packet(DEMO_RADIO_CHANNEL);
    (void)tx_status; // Suppress unused variable warning if logging/assertions are omitted

    // // 2. Retrieve all received packets currently pending in the RX queue
    // uint16_t packet_length = 0;
    // while (app_radio_get_packet(app_rx_buffer, &packet_length, sizeof(app_rx_buffer))) {
    //   // Process or log the received packet here
    //   // Example: app_rx_buffer contains packet_length bytes of data
    // }
  }

  return process_count;
}

const split_interface_t non_legal_split_interface
__attribute__((section(".split_interface"), used)) = {
  .magic = SPLIT_INTERFACE_MAGIC,
  .abi_version = SPLIT_INTERFACE_ABI_VERSION,
  .size = sizeof(split_interface_t),
  .init = non_legal_init,
  .process_action = non_legal_process_action,
  .ccm_encrypt = radio_ccm_encrypt,
  .ccm_decrypt = radio_ccm_decrypt,
  .radio_test = radio_ccm_test,
  .vector_table = __VECTOR_TABLE,
  .vector_table_entries = 16U + EXT_IRQ_COUNT,
};

void app_init(void)
{
}

void app_process_action(void)
{
}
