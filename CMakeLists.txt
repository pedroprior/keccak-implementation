cmake_minimum_required(VERSION 3.10)

project(KeccakProject C)
set(CMAKE_C_STANDARD 99)

add_executable(keccak_program
    src/main.c
    src/keccak.c
    src/technicalities.c
)

target_include_directories(keccak_program PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(keccak_program PRIVATE -g)
endif()

target_compile_options(keccak_program PRIVATE -Wall -Wextra)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)