cmake_minimum_required(VERSION 3.16)
project(cpu)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -fsanitize=address,leak,undefined")

set(core_sources main.cpp src/cpu.cpp include/component_type.h)

add_executable(cpu ${core_sources})
target_link_libraries(cpu /usr/local/lib/libfmt.a)
target_include_directories(cpu PUBLIC include)