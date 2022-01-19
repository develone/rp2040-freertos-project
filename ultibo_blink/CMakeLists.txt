cmake_minimum_required(VERSION 3.12)

#include(pico_sdk_import.cmake)

project(pico-projects)

pico_sdk_init()

add_executable(ultibo_blink
    ultibo_blink.c
)

target_link_libraries(ultibo_blink pico_stdlib)

pico_enable_stdio_usb(ultibo_blink 1)
pico_enable_stdio_uart(ultibo_blink 0)

pico_add_extra_outputs(ultibo_blink)
