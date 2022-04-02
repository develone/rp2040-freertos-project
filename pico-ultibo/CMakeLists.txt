add_executable(pico-ultibo
        main.c
)

target_link_libraries(pico-ultibo pico_stdlib freertos)

pico_enable_stdio_usb(pico-ultibo 1)
pico_enable_stdio_uart(pico-ultibo 0)

pico_add_extra_outputs(pico-ultibo)