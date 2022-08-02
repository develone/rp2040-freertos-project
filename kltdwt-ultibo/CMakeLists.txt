add_executable(kltdwt-ultibo
        main.c
)

target_link_libraries(kltdwt-ultibo pico_stdlib lifting crc_crc16 cir-buf klt)
pico_add_extra_outputs(kltdwt-ultibo)
pico_enable_stdio_usb(kltdwt-ultibo 1)
pico_enable_stdio_uart(kltdwt-ultibo 0)
