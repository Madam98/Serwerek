cmake_minimum_required(VERSION 3.21)
project(klient C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS -pthread)

find_package(Threads REQUIRED)

add_executable(klient client.c client.c)
target_link_libraries(klient pthread)