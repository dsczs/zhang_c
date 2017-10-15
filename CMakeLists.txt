cmake_minimum_required(VERSION 3.7)
project(c1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c
        nginx-1.13.5.tar.gz
        test
        nginx
        redis
        datastruct
        glibc
        lamp_linux
        lamp_shell
        nginx-1.13.5
        redis-3.2.11
        麦子学院进程教程
        )
add_executable(c1 ${SOURCE_FILES})