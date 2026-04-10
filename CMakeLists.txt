cmake_minimum_required(VERSION 4.1)
project(TetrisTimeAttack C)

set(CMAKE_C_STANDARD 11)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(TetrisTimeAttack Source/TetrisTimeAttack.c
        Source/TetrisTimeAttack.h)
target_link_libraries(TetrisTimeAttack ${CURSES_LIBRARY})
