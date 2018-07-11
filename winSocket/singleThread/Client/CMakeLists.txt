cmake_minimum_required(VERSION 3.8)
project(WinSock)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES client.c log.h)
link_libraries(ws2_32 wsock32)

add_executable(WinSock ${SOURCE_FILES})