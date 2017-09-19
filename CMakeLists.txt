cmake_minimum_required(VERSION 3.7)
project(zhang_c)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/zhang_c.cbp
        cmake-build-debug/zhang_c.exe
        CMakeLists.txt
        test/test.c)

add_executable(zhang_c ${SOURCE_FILES})