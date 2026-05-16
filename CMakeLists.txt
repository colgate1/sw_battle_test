cmake_minimum_required(VERSION 3.27)
project(sw_battle_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        src/*.hpp
)

add_executable(sw_battle_test ${SOURCES})

target_include_directories(sw_battle_test PRIVATE src)