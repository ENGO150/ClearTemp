cmake_minimum_required(VERSION 3.21)
project(ClearTemp C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(lib/engodatabase)

add_executable(ClearTemp
        include/api.h
        include/tools.h
        lib/engodatabase/edb.c
        lib/engodatabase/edb.h
        src/assets/api.c
        src/assets/tools.c
        src/main.c)
