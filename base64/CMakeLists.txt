cmake_minimum_required(VERSION 3.8)
project(base64)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c encode.c encode.h decode.c decode.h)
add_executable(base64 ${SOURCE_FILES})
