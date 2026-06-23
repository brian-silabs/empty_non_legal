/***************************************************************************//**
 * @file
 * @brief Callable side of the fixed-address split PoC.
 ******************************************************************************/

#include "../empty/split_interface.h"

#include <stdbool.h>

static uint32_t process_count;
static bool initialized;

static void non_legal_init(void)
{
  process_count = 0U;
  initialized = true;
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
};

void app_init(void)
{
}

void app_process_action(void)
{
}
