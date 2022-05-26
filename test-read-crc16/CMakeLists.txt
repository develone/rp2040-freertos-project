add_executable(test-read-crc16
        main.c crc16.h xreceive.h xtransmit.h fs.h vi.h pshell.h
)

target_link_libraries(test-read-crc16 pico_stdlib freertos lifting crc16 klt)

pico_enable_stdio_usb(test-read-crc16 1)
pico_enable_stdio_uart(test-read-crc16 1)

pico_add_extra_outputs(test-read-crc16)
