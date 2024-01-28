cmake_minimum_required(VERSION 3.22)

project(tinyrenderer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main main.cpp tgaimage.h tgaimage.cpp)