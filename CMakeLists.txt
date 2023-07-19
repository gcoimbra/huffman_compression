cmake_minimum_required(VERSION 2.8)
SET(-GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -lm -O0 -ggdb -g -std=c11")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_library(CodigosCompressao Compression.c)
add_subdirectory (ArvoreBinaria)
add_subdirectory (Stringzao)

add_executable(main main.c)
target_link_libraries(main PUBLIC m CodigosCompressao Stringzao ArvoreBinaria)