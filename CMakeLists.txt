cmake_minimum_required(VERSION 3.7)
project(cppbasic)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -fno-elide-constructors)
set(CMAKE_CXX_FLAGS -Wpadded)

add_subdirectory(cppbasic)