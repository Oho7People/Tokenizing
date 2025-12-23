cmake_minimum_required(VERSION 3.10)
project(Tokenize VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(calc
    src/main.cpp
    src/calculator.cpp
    src/parser.cpp
    src/tokenize.cpp
)

target_include_directories(calc PRIVATE include)

target_compile_options(calc PRIVATE -Wall -Wextra -Wpedantic)