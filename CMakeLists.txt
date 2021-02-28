cmake_minimum_required(VERSION 1.15)
project(2048)
add_executable(2048 main.c board.c)
target_include_directories(2048 PRIVATE .)
