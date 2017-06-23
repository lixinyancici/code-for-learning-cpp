cmake_minimum_required(VERSION 3.7)
project(cppbasic)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -Wpadded)
set(CMAKE_CXX_FLAGS -fno-elide-constructors)

add_subdirectory(cppbasic)