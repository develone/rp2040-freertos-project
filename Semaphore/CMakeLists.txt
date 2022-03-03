add_executable(Semaphore
        main.c
)

pico_enable_stdio_usb(Semaphore 1)
pico_enable_stdio_uart(Semaphore 0)

target_link_libraries(Semaphore pico_stdlib freertos)
pico_add_extra_outputs(Semaphore)
