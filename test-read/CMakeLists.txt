add_executable(test-read
        main.c
)

target_link_libraries(test-read pico_stdlib freertos lifting crc klt)

pico_enable_stdio_usb(test-read 1)
pico_enable_stdio_uart(test-read 0)

pico_add_extra_outputs(test-read)