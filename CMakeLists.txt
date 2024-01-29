cmake_minimum_required(VERSION 3.22)

project(tinyrenderer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRCS ./*.cpp  ./*.h)
add_executable(main ${SRCS})

target_include_directories(main PRIVATE ./)