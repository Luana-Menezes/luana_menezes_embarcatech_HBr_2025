cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(temperature_reader C CXX ASM)


pico_sdk_init()

add_library(unity STATIC
    tests/unity/unity.c
)
target_include_directories(unity PUBLIC
    tests/unity
)

add_executable(temperature_reader
    temperature_reader.c
)

target_link_libraries(temperature_reader
    pico_stdlib
    hardware_adc
)

pico_enable_stdio_usb(temperature_reader 1)
pico_enable_stdio_uart(temperature_reader 0)
pico_add_extra_outputs(temperature_reader)

add_executable(test_runner
    tests/test_temperature_reader.c
)

target_compile_definitions(test_runner PRIVATE
    UNIT_TESTING
)

# Link with required libraries including Unity and temperature_reader code
target_sources(test_runner PRIVATE
    temperature_reader.c
)

target_link_libraries(test_runner
    pico_stdlib
    hardware_adc
    unity
)

pico_enable_stdio_usb(test_runner 1)
pico_enable_stdio_uart(test_runner 0)
pico_add_extra_outputs(test_runner)


