cmake_minimum_required(VERSION 3.28)
project(Lab3 C)

set(CMAKE_C_STANDARD 23)

add_executable(Lab3 main.c
        SMatrix.h
        Vector.h
        Vector.c
)
