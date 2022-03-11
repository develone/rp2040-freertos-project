set(PICO_SDK_CRC_SOURCE CRC-Files)

add_library(crc
    ${PICO_SDK_CRC_SOURCE}/crc.c
		${PICO_SDK_CRC_SOURCE}/head-tail.c
		${PICO_SDK_CRC_SOURCE}/cvtutils.c
)

target_include_directories(crc PUBLIC
    .
    ${PICO_SDK_CRC_SOURCE}/include
    ${PICO_SDK_CRC_SOURCE}/portable/GCC/ARM_CM0
)
