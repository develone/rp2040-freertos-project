add_executable(Mutex
        main.c
)

pico_enable_stdio_usb(Mutex 1)
pico_enable_stdio_uart(Mutex 0)

target_link_libraries(Mutex pico_stdlib freertos)
pico_add_extra_outputs(Mutex)
