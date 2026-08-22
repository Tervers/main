cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(keyclicker C CXX ASM)

set(PICO_PARAM_ASSERTIONS_ENABLED 1)

pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(keyclicker
    keyclicker.c
		sources/angle.c
		sources/calculations.c
		sources/display.c
		sources/gpioF.c
		sources/timeF.c
)

target_link_libraries(keyclicker
    hardware_gpio
    hardware_adc
    hardware_pwm
    pico_multicore
    pico_rand
    pico_stdlib
    pico_time
)

pico_enable_stdio_usb(keyclicker 1)
pico_enable_stdio_uart(keyclicker 0)
pico_add_extra_outputs(keyclicker)
