cmake_minimum_required(VERSION 1.15)
project(2048-cli)

add_library(board src/board.c)
target_include_directories(board PUBLIC src)

add_executable(2048-cli src/main.c)
target_link_libraries(2048-cli board)

add_subdirectory(lib/googletest)
enable_testing()
add_executable(test_board test/board.cpp)
target_include_directories(test_board PRIVATE ${gtest_SOURCE_DIR}/include
    ${gtest_SOURCE_DIR})
target_link_libraries(test_board board gtest gtest_main)
add_test(NAME board COMMAND test_board)
