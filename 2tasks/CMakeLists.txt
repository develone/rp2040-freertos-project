add_executable(2tasks
        main.c
)

target_link_libraries(2tasks pico_stdlib freertos)

pico_enable_stdio_usb(2tasks 1)
pico_enable_stdio_uart(2tasks 0)

pico_add_extra_outputs(2tasks)