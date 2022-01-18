add_executable(pico-lifting
        main.c
)

target_link_libraries(pico-lifting pico_stdlib lifting)
pico_add_extra_outputs(pico-lifting)
pico_enable_stdio_usb(pico-lifting 1)
pico_enable_stdio_uart(pico-lifting 0)
