cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(keyclicker C CXX ASM)

set(PICO_PARAM_ASSERTIONS_ENABLED 1)

pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(keyclicker
    keyclicker.c
)

target_link_libraries(keyclicker
    pico_stdlib
    hardware_gpio
    hardware_adc
    hardware_pwm
    pico_time
)

pico_add_extra_outputs(keyclicker)
