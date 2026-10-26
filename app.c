/***************************************************************************//**
 * @file
 * @brief Callable side of the fixed-address split PoC.
 ******************************************************************************/

#include "../empty/split_interface.h"

#include <stdbool.h>
#include <string.h>
#include "radio_ccm.h"
#include "sli_protocol_crypto.h"
#include "app_radio.h"

#define DEMO_RADIO_CHANNEL 19U
#define APP_RX_BUFFER_SIZE 128U

static uint32_t process_count;
static bool initialized;
static uint8_t app_rx_buffer[APP_RX_BUFFER_SIZE];

/* Reset_Handler is never entered by the host. Initialize this image's RAM
 * before touching module/SDK globals, without resetting clocks or peripherals.
 * init is called once at boot, before any module users exist. */
static sl_status_t non_legal_init(void)
{
  //TODO Check why Codex added RAM init
  extern uint8_t __etext[], __data_start__[], __data_end__[];
  extern uint8_t __bss_start__[], __bss_end__[];
  extern uint8_t __lma_ramfuncs_start__[], __vma_ramfuncs_start__[];
  extern uint8_t __vma_ramfuncs_end__[];
  memcpy(__data_start__, __etext,
         (size_t)(__data_end__ - __data_start__));
  memset(__bss_start__, 0, (size_t)(__bss_end__ - __bss_start__));
  memcpy(__vma_ramfuncs_start__, __lma_ramfuncs_start__,
         (size_t)(__vma_ramfuncs_end__ - __vma_ramfuncs_start__));

  app_radio_init();
  //app_radio_start_rx_channel(DEMO_RADIO_CHANNEL);


  sl_status_t status = sli_protocol_crypto_init();
  if (status != SL_STATUS_OK) { return status; }
  /* Seed before the legal SE worker starts: SDK masking uses SE entropy. */
  sli_aes_seed_mask();
  process_count = 0U;
  initialized = true;
  return SL_STATUS_OK;
}

static uint32_t non_legal_process_action(void)
{
  if (initialized) {
    process_count++;
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
};

void app_init(void)
{
}

void app_process_action(void)
{
}
