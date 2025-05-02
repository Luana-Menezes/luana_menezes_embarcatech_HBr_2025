cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(temperature_reader_tests C CXX ASM)
pico_sdk_init()

include(FetchContent)
FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.5.2
)
FetchContent_MakeAvailable(unity)

include_directories(${unity_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(test_runner
    test_temperature_reader.c
    ${unity_SOURCE_DIR}/src/unity.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../temperature_reader.c
)

target_link_libraries(test_runner
    pico_stdlib
    hardware_adc
)

pico_enable_stdio_usb(test_runner 1)
pico_enable_stdio_uart(test_runner 0)

pico_add_extra_outputs(test_runner)
