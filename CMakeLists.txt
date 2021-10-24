cmake_minimum_required(VERSION 3.21)
project(elf)

set(CMAKE_CXX_STANDARD 17)

add_library(elf STATIC
        src/elf.cpp src/section.cpp src/elf_base.cpp)
target_include_directories(elf PUBLIC include)


add_executable(elf_test test.cpp)
target_link_libraries(elf_test elf)
