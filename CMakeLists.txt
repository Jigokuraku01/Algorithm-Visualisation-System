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

file(GLOB_RECURSE FILES_IN_SRC "src/*")

set(SRC_FILES "")

foreach(FILE ${FILES_IN_SRC})
    if(FILE MATCHES "\\.cpp$" OR FILE MATCHES "\\.c$")
        list(APPEND SRC_FILES ${FILE})
        message(STATUS "Source file: ${FILE}")
    endif()
endforeach()

file(GLOB_RECURSE INCLUDE_DIRS_AND_FILES LIST_DIRECTORIES true "include/*")

set(INCLUDE_DIRS "")

foreach(FILE ${INCLUDE_DIRS_AND_FILES})
    if (IS_DIRECTORY ${FILE})
        list(APPEND INCLUDE_DIRS ${FILE})
        message(STATUS "Include directory: ${FILE}")
    endif()    
endforeach()

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${INCLUDE_DIRS}
)

target_compile_options(${PROJECT_NAME}  PRIVATE ${Flags})

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics sfml-window sfml-system
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core Qt6::Gui Qt6::Widgets
)
