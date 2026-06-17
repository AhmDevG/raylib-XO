cmake_minimum_required(VERSION 3.15)

project(raylib_XO)

set(CMAKE_CXX_STANDARD 17)

add_executable(raylib_XO src/main.cpp)

target_include_directories(raylib_XO PRIVATE include)

target_link_directories(raylib_XO PRIVATE lib)

target_link_libraries(raylib_XO
    raylib
    gdi32
    winmm
    opengl32
)
