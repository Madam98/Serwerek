cmake_minimum_required(VERSION 3.21)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(serwer C)


set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS -pthread)
set(INCLUDE_DIRECTORIES ./)
include_directories( ./ )

find_package(Threads REQUIRED)

add_executable(serwer main.c cmake-build-debug/
        Headers/headers/headers.h
        Headers/data/variables.h
        Headers/data/structs.h
        Headers/file_opearation/readstring.h
        Headers/file_opearation//createfolder.h
        Headers/file_opearation/msleep.h
        Headers/file_opearation/textAnimation.h
        Headers/connect_operation/createconnectionfunctions.h
        Headers/arrayfunctions.h
        Headers/commands/touch.h
        Headers/commands/share.h
        Headers/commands/list.h
        Headers/handler/sigsegv.h Headers/commands/delete.h Headers/commands/copy.h Headers/commands/rename.h Headers/executecommand.h Headers/commands/add.h Headers/commands/enter_file.h Headers/commands/message.h Headers/lists.h Headers/insertchar.h Headers/deletechar.h)
target_link_libraries(serwer pthread)
