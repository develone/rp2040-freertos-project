add_executable(Scheduling
        main.c
)

pico_enable_stdio_usb(Scheduling 1)
pico_enable_stdio_uart(Scheduling 0)

target_link_libraries(Scheduling pico_stdlib freertos)
pico_add_extra_outputs(Scheduling)