cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_FETCH_FROM_GIT on)
include(pico_sdk_import.cmake)

project(toasterpwn)

pico_sdk_init()



add_executable(toasterpwn
    toasterpwn.c
    user_interface.c
    lcd_1602_i2c.c
)

pico_enable_stdio_usb(toasterpwn 1)
pico_enable_stdio_uart(toasterpwn 0)

target_link_libraries(toasterpwn pico_stdlib hardware_i2c)

pico_add_extra_outputs(toasterpwn)
