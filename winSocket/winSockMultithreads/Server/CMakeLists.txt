cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES server.cpp)
link_directories(dll/x86)

link_libraries(ws2_32 wsock32)
link_libraries( pthreadGC2.dll pthreadVC2.dll)

add_executable(Server ${SOURCE_FILES})




