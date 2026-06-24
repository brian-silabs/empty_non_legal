####################################################################
# Automatically-generated file. Do not edit!                       #
####################################################################

set(SDK_PATH "/Users/brrodrig/.silabs/slt/installs/conan/p/simplfa179856e7001/p")
set(COPIED_SDK_PATH "simplicity_sdk_2025.6.3")
set(PKG_PATH "/Users/brrodrig/.silabs/slt/installs")

add_library(slc OBJECT
    "../${COPIED_SDK_PATH}/hardware/board/src/sl_board_control_gpio.c"
    "../${COPIED_SDK_PATH}/hardware/board/src/sl_board_init.c"
    "../${COPIED_SDK_PATH}/hardware/driver/configuration_over_swo/src/sl_cos.c"
    "../${COPIED_SDK_PATH}/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_eusart/sl_mx25_flash_shutdown.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_assert.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_core_cortexm.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_syscalls.c"
    "../${COPIED_SDK_PATH}/platform/Device/SiliconLabs/EFR32MG24/Source/startup_efr32mg24.c"
    "../${COPIED_SDK_PATH}/platform/Device/SiliconLabs/EFR32MG24/Source/system_efr32mg24.c"
    "../${COPIED_SDK_PATH}/platform/driver/debug/src/sl_debug_swo.c"
    "../${COPIED_SDK_PATH}/platform/driver/gpio/src/sl_gpio.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_cmu.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_emu.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_eusart.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_gpio.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_msc.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_system.c"
    "../${COPIED_SDK_PATH}/platform/peripheral/src/sl_hal_gpio.c"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/src/sl_clock_manager.c"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/src/sl_clock_manager_hal_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/src/sl_clock_manager_init.c"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/src/sl_clock_manager_init_hal_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_init/src/sl_device_init_dcdc_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_init/src/sl_device_init_emu_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_manager/clocks/sl_device_clock_efr32xg24.c"
    "../${COPIED_SDK_PATH}/platform/service/device_manager/src/sl_device_clock.c"
    "../${COPIED_SDK_PATH}/platform/service/device_manager/src/sl_device_gpio.c"
    "../${COPIED_SDK_PATH}/platform/service/interrupt_manager/src/sl_interrupt_manager_cortexm.c"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/src/sl_memory_manager_region.c"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/src/sl_main_init.c"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/src/sl_main_init_memory.c"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/src/sl_main_process_action.c"
    "../${COPIED_SDK_PATH}/platform/service/udelay/src/sl_udelay.c"
    "../${COPIED_SDK_PATH}/platform/service/udelay/src/sl_udelay_armv6m_gcc.S"
    "../app.c"
    "../autogen/sl_board_default_init.c"
    "../autogen/sl_event_handler.c"
    "../main.c"
)

target_include_directories(slc PUBLIC
   "../config"
   "../autogen"
   "../."
    "../${COPIED_SDK_PATH}/platform/Device/SiliconLabs/EFR32MG24/Include"
    "../${COPIED_SDK_PATH}/hardware/board/inc"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/inc"
    "../${COPIED_SDK_PATH}/platform/service/clock_manager/src"
    "../${COPIED_SDK_PATH}/platform/CMSIS/Core/Include"
    "../${COPIED_SDK_PATH}/platform/common/inc"
    "../${COPIED_SDK_PATH}/hardware/driver/configuration_over_swo/inc"
    "../${COPIED_SDK_PATH}/platform/driver/debug/inc"
    "../${COPIED_SDK_PATH}/platform/service/device_manager/inc"
    "../${COPIED_SDK_PATH}/platform/service/device_init/inc"
    "../${COPIED_SDK_PATH}/platform/emlib/inc"
    "../${COPIED_SDK_PATH}/platform/driver/gpio/inc"
    "../${COPIED_SDK_PATH}/platform/peripheral/inc"
    "../${COPIED_SDK_PATH}/platform/service/interrupt_manager/inc"
    "../${COPIED_SDK_PATH}/platform/service/interrupt_manager/src"
    "../${COPIED_SDK_PATH}/platform/service/interrupt_manager/inc/arm"
    "../${COPIED_SDK_PATH}/platform/service/memory_manager/inc"
    "../${COPIED_SDK_PATH}/hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_eusart"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/inc"
    "../${COPIED_SDK_PATH}/platform/service/sl_main/src"
    "../${COPIED_SDK_PATH}/platform/service/udelay/inc"
)

target_compile_definitions(slc PUBLIC
    "DEBUG_EFM=1"
    "EFR32MG24B210F1536IM48=1"
    "SL_CODE_COMPONENT_SYSTEM=system"
    "SL_BOARD_NAME=\"BRD4186C\""
    "SL_BOARD_REV=\"A01\""
    "HARDWARE_BOARD_DEFAULT_RF_BAND_2400=1"
    "HARDWARE_BOARD_SUPPORTS_1_RF_BAND=1"
    "HARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1"
    "HFXO_FREQ=39000000"
    "SL_CODE_COMPONENT_CLOCK_MANAGER=clock_manager"
    "SL_COMPONENT_CATALOG_PRESENT=1"
    "SL_CODE_COMPONENT_GPIO=gpio"
    "SL_CODE_COMPONENT_HAL_COMMON=hal_common"
    "SL_CODE_COMPONENT_HAL_GPIO=hal_gpio"
    "SL_CODE_COMPONENT_INTERRUPT_MANAGER=interrupt_manager"
    "CMSIS_NVIC_VIRTUAL=1"
    "CMSIS_NVIC_VIRTUAL_HEADER_FILE=\"cmsis_nvic_virtual.h\""
    "SL_CODE_COMPONENT_CORE=core"
)

target_link_libraries(slc PUBLIC
    "-Wl,--start-group"
    "gcc"
    "c"
    "m"
    "nosys"
    "-Wl,--end-group"
)
target_compile_options(slc PUBLIC
    $<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:C>:-mthumb>
    $<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>
    $<$<COMPILE_LANGUAGE:C>:-mcmse>
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>
    $<$<COMPILE_LANGUAGE:C>:-Os>
    $<$<COMPILE_LANGUAGE:C>:-fdata-sections>
    $<$<COMPILE_LANGUAGE:C>:-ffunction-sections>
    $<$<COMPILE_LANGUAGE:C>:-fomit-frame-pointer>
    $<$<COMPILE_LANGUAGE:C>:-g>
    $<$<COMPILE_LANGUAGE:C>:-fno-lto>
    $<$<COMPILE_LANGUAGE:C>:--specs=nano.specs>
    $<$<COMPILE_LANGUAGE:CXX>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:CXX>:-mthumb>
    $<$<COMPILE_LANGUAGE:CXX>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:CXX>:-mfloat-abi=hard>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-mcmse>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
    $<$<COMPILE_LANGUAGE:CXX>:-Os>
    $<$<COMPILE_LANGUAGE:CXX>:-fdata-sections>
    $<$<COMPILE_LANGUAGE:CXX>:-ffunction-sections>
    $<$<COMPILE_LANGUAGE:CXX>:-fomit-frame-pointer>
    $<$<COMPILE_LANGUAGE:CXX>:-g>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-lto>
    $<$<COMPILE_LANGUAGE:CXX>:--specs=nano.specs>
    $<$<COMPILE_LANGUAGE:ASM>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:ASM>:-mthumb>
    $<$<COMPILE_LANGUAGE:ASM>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:ASM>:-mfloat-abi=hard>
    "$<$<COMPILE_LANGUAGE:ASM>:SHELL:-x assembler-with-cpp>"
)

set(post_build_command )
set_property(TARGET slc PROPERTY C_STANDARD 17)
set_property(TARGET slc PROPERTY CXX_STANDARD 17)
set_property(TARGET slc PROPERTY CXX_EXTENSIONS OFF)

target_link_options(slc INTERFACE
    -mcpu=cortex-m33
    -mthumb
    -mfpu=fpv5-sp-d16
    -mfloat-abi=hard
    -T${CMAKE_CURRENT_LIST_DIR}/../autogen/linkerfile.ld
    --specs=nano.specs
    "SHELL:-Xlinker -Map=$<TARGET_FILE_DIR:empty_non_legal>/empty_non_legal.map"
    -fno-lto
    -Wl,--gc-sections
)

# BEGIN_SIMPLICITY_STUDIO_METADATA=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END_SIMPLICITY_STUDIO_METADATA