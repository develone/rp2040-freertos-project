set(PICO_SDK_CRC16_SOURCE CRC16-Files)

add_library(crc16
    ${PICO_SDK_CRC16_SOURCE}/crc16.c
		${PICO_SDK_CRC16_SOURCE}/head-tail.c
		${PICO_SDK_CRC16_SOURCE}/cvtutils.c
 

			
)

target_include_directories(crc16 PUBLIC
    .
    ${PICO_SDK_CRC16_SOURCE}/include
		${PICO_SDK_CRC16_SOURCE}/hardware
		
    ${PICO_SDK_CRC16_SOURCE}/portable/GCC/ARM_CM0
)
