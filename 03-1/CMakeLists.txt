cmake_minimum_required(VERSION 2.8)

project(03-1_santas-suit)
add_executable(${PROJECT_NAME} "main.cpp")

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt
)
add_definitions(-std=c++11)
