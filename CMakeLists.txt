cmake_minimum_required(VERSION 3.16)
project(cpu)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -fsanitize=address,leak,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

set(core_sources
        src/system_components.cpp
        src/cpu/cpu.cpp
        src/cpu/reg_manipulate.cpp
        src/cpu/instruction_implement/cycle_tools.cpp
        src/cpu/register/register.cpp
        src/cpu/register/to_string.cpp
        src/cpu/to_string.cpp
        src/cpu/register/register.cpp
        src/cpu/register/to_string.cpp
        src/mmu/mmu.cpp
        include/cpu/register/register.h src/cpu/reg_manipulate.cpp
        src/mmu/general_memory.cpp
        src/mmu/display_memory.cpp
        src/mmu/gamepak_memory.cpp
        src/cpu/instruction_implement/arm_alu_type1.cpp
        src/cpu/instruction_implement/cpsr_modify.cpp
        src/cpu/instruction_implement/arm_alu_type2.cpp src/cpu/instruction_implement/arm_alu_type3.cpp)

set(core_headers
        include
        include/cpu
        include/cpu/register
        include/cpu/instruction_implement
        include/gg_utility
        include/mmu
        include/mmu/IO
        include/disassembler
        include/disassembler/disassemble
        include/disassembler/disassemble/decoder/arm
        include/disassembler/disassemble/decoder/thumb
        include/disassembler/disassemble/formatter
        include/disassembler/disassemble/information
        include/cpu/instruction_implement/
        include/cpu/instruction_implement/arm
        )

set(decoder_sources
        src/disassembler/arm_disassembler/to_string.cpp
        src/disassembler/thumb_disassembler/thumb_formatter.cpp
        src/disassembler/instruction.cpp
        src/disassembler/disassembler.cpp)

add_executable(cpu main.cpp ${core_sources} ${core_headers} ${decoder_sources})
target_link_libraries(cpu /usr/local/lib/libfmt.a)
target_include_directories(cpu PUBLIC ${core_headers})

project(test)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -fsanitize=address,leak,undefined")

set(test_sources test/mmu/write_test.cpp)

add_executable(test test/catch.hpp ${core_sources} ${core_headers} ${test_sources})
target_link_libraries(test /usr/local/lib/libfmt.a)
target_include_directories(test PUBLIC
        include
        include/cpu
        include/gg_utility
        include/mmu
        include/mmu/IO
        test
        test/mmu
        )