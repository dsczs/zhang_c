cmake_minimum_required(VERSION 3.7)
project(zhang_c)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c
        nginx
        lamp_linux
        lamp_shell
        redis
        nginx-1.13.5
        redis-3.2.11
        test
        glibc
        datastruct

        datastruct/第3章链表/04双向链表.c datastruct/第3章链表/05循环链表.c)

add_executable(zhang_c ${SOURCE_FILES})

#cmake_minimum_required(VERSION 3.8)
#project(c1)
#
#set(CMAKE_C_STANDARD 99)
#
#set(SOURCE_FILES main.c
#        nginx-1.13.5.tar.gz
#        test
#        nginx
#        redis
#        datastruct
#        glibc
#        lamp_linux
#        lamp_shell
#        nginx-1.13.5
#        redis-3.2.11
#        )
#add_executable(c1 ${SOURCE_FILES})