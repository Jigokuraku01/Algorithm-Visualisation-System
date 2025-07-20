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

set(INCLUDE_HEADERS "")

foreach(FILE ${INCLUDE_DIRS_AND_FILES})
    if (IS_DIRECTORY ${FILE})
        list(APPEND INCLUDE_DIRS ${FILE})
        message(STATUS "Include directory: ${FILE}")
    else()
        if(FILE MATCHES "\\.hpp$" OR FILE MATCHES "\\.h$")
            list(APPEND INCLUDE_HEADERS ${FILE})
        endif()
    endif()    
endforeach()

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Quick)

add_executable(${PROJECT_NAME}
               ${SRC_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${INCLUDE_DIRS}
)

target_compile_options(${PROJECT_NAME} PRIVATE ${Flags})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Quick
)

find_program(CLANG_TIDY NAMES clang-tidy-18)

set(LINT_FILES ${INCLUDE_HEADERS} ${SRC_FILES})

if(CLANG_TIDY)
    execute_process(
        COMMAND ${CLANG_TIDY} --help
        OUTPUT_VARIABLE TIDY_HELP_OUTPUT
    )
    
    set(SUPPORTS_JOBS FALSE)
    if(TIDY_HELP_OUTPUT MATCHES "\\-j\\ <N>")
        set(SUPPORTS_JOBS TRUE)
    elseif(TIDY_HELP_OUTPUT MATCHES "\\-j")
        set(SUPPORTS_JOBS TRUE)
    endif()

    if (${SUPPORTS_JOBS})
        message(STATUS "Your version of clang-tidy supports the -j option.")
    else()
        message(WARNING "Your version of clang-tidy does not support the -j option.")    
    endif()

    set(TIDY_COMMAND ${CLANG_TIDY}
        ${LINT_FILES}
        --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
        --header-filter=.*
        -p ${CMAKE_BINARY_DIR}
    )

    if(SUPPORTS_JOBS)
        list(APPEND TIDY_COMMAND "-j 0")
    endif()

    add_custom_target(lint
        COMMAND ${TIDY_COMMAND}
        COMMENT "Running clang-tidy."
    )
else()
    message(WARNING "clang-tidy not found, lint target off.")
endif()

add_custom_target(build
    DEPENDS ${PROJECT_NAME}
    COMMENT "Building project."
)

add_custom_target(clear
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
    COMMENT "Cleaning up generated files."
)

add_custom_target(build_and_run
    DEPENDS ${PROJECT_NAME}
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    COMMENT "Building and running ${PROJECT_NAME}"
)
с