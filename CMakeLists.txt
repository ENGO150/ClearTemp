cmake_minimum_required(VERSION 3.21)
project(ClearTemp C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(lib/engodatabase)

add_executable(ClearTemp
        src/main.c
        src/assets/api.c
        src/assets/tools.c
        src/assets/flags.c
        include/api.h
        include/tools.h
        include/flags.h
        lib/engodatabase/edb.c
        lib/engodatabase/edb.h)
