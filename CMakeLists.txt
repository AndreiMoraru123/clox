cmake_minimum_required(VERSION 3.27)
project(clox C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(clox
        chunk.c
        memory.c
        memory.h
        chunk.h
        common.h
        main.c
        debug.h
        debug.h
        debug.c
        value.c
        value.h
        vm.c
        vm.h
        compiler.c
        compiler.h
        scanner.c
        scanner.h
        object.c
        object.h
        table.c
        table.h)
