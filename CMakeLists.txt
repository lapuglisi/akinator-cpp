cmake_minimum_required(VERSION 3.0)

project(akinator)

FILE(GLOB akinator_sources *.cpp)

add_compile_options(-std=c++11 -ggdb)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${CMAKE_PROJECT_NAME} ${akinator_sources})