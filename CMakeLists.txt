cmake_minimum_required(VERSION 3.10)

project(RRS LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_DIR ${PROJECT_SOURCE_DIR}/dependencies/SDL2-2.30.10)

find_package(SDL2 REQUIRED)

add_executable(RRS
    src/main.cpp
)

target_link_libraries(RRS PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
)

target_include_directories(RRS PRIVATE
    ${PROJECT_BINARY_DIR}
    include
)
