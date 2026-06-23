####################################################################
# Automatically-generated file. Do not edit!                       #
####################################################################

set(SDK_PATH "/Users/brian/.silabs/slt/installs/conan/p/simplfa179856e7001/p")
set(COPIED_SDK_PATH "simplicity_sdk_2025.6.3")
set(PKG_PATH "/Users/brian/.silabs/slt/installs")

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

# BEGIN_SIMPLICITY_STUDIO_METADATA=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=END_SIMPLICITY_STUDIO_METADATA