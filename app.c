/***************************************************************************//**
 * @file
 * @brief Callable side of the fixed-address split PoC.
 ******************************************************************************/

#include "../empty/split_interface.h"

#include <stdbool.h>
#include <string.h>
#include "radio_ccm.h"
#include "sli_protocol_crypto.h"

static uint32_t process_count;
static bool initialized;

/* Reset_Handler is never entered by the host. Initialize this image's RAM
 * before touching module/SDK globals, without resetting clocks or peripherals.
 * init is called once at boot, before any module users exist. */
static sl_status_t non_legal_init(void)
{
  extern uint8_t __etext[], __data_start__[], __data_end__[];
  extern uint8_t __bss_start__[], __bss_end__[];
  extern uint8_t __lma_ramfuncs_start__[], __vma_ramfuncs_start__[];
  extern uint8_t __vma_ramfuncs_end__[];
  memcpy(__data_start__, __etext,
         (size_t)(__data_end__ - __data_start__));
  memset(__bss_start__, 0, (size_t)(__bss_end__ - __bss_start__));
  memcpy(__vma_ramfuncs_start__, __lma_ramfuncs_start__,
         (size_t)(__vma_ramfuncs_end__ - __vma_ramfuncs_start__));
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
