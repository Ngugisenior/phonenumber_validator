# cmake_minimum_required(VERSION <specify CMake version here>)
project(phone_num_c C)

set(CMAKE_C_STANDARD 11)

add_executable(phone_num_c
        main.c
        val.c)
