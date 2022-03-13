set(PICO_SDK_KLT_SOURCE KLT-Kernel)

add_library(klt
    ${PICO_SDK_KLT_SOURCE}/selectGoodFeatures.c
    ${PICO_SDK_KLT_SOURCE}/pyramid.c
    ${PICO_SDK_KLT_SOURCE}/convolve.c
    ${PICO_SDK_KLT_SOURCE}/error.c
    ${PICO_SDK_KLT_SOURCE}/klt.c
    ${PICO_SDK_KLT_SOURCE}/klt_util.c
    ${PICO_SDK_KLT_SOURCE}/portable/MemMang/heap_3.c
    ${PICO_SDK_KLT_SOURCE}/portable/GCC/ARM_CM0/port.c
)

target_include_directories(klt PUBLIC
    .
    ${PICO_SDK_KLT_SOURCE}/include
    ${PICO_SDK_KLT_SOURCE}/portable/GCC/ARM_CM0
)
