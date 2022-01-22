set(PICO_SDK_LIFTING_SOURCE LIFTING-Files)

add_library(lifting
    ${PICO_SDK_LIFTING_SOURCE}/lifting.c
		  
)

target_include_directories(lifting PUBLIC
    .
    ${PICO_SDK_LIFTING_SOURCE}/include
    ${PICO_SDK_LIFTING_SOURCE}/portable/GCC/ARM_CM0
)
