cmake_minimum_required(VERSION 3.15)
project(VisualizationProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-18")

set(CMAKE_CXX_CLANG_TIDY 
    clang-tidy;
    --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy;
    --header-filter=.*
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

set(Flags
    -O2
    -Werror
    -pedantic-errors

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/scenes/*.cpp"
    "src/scenes/algo_handler/*.cpp"
    "src/scenes/algo_handler/algorithms/*.cpp"
    "src/scenes/menu/*.cpp"
    "src/utilities/*.cpp"
    "src/objects/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "include/*.hpp"
    "include/scenes/*.hpp"
    "include/scenes/algo_handler/*.hpp"
    "src/scenes/algo_handler/algorithms/*.hpp"
    "include/scenes/menu/*.hpp"
    "include/utilities/*.hpp"
    "src/objects/*.cpp"
)

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(${PROJECT_NAME}  PRIVATE ${CFlag})
