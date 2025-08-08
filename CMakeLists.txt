cmake_minimum_required(VERSION 3.22.1)

project(CLox VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS_DEBUG "-g -O0")

file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include/)
