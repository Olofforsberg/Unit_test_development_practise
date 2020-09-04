# Get the folder name from the current directory
get_filename_component(folder ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Basic CMake project
cmake_minimum_required(VERSION 3.5.1)

# Name the project after the folder
project(${folder} CXX)

# Get a source filename from the folder name by replacing -'s with _'s
string(REPLACE "-" "_" file ${folder})

# Implementation file
set(binary_tree ${file}.cpp)

# Use the common Catch library
add_executable(${folder} ${file}_test.cpp ${binary_tree} ${file}.h test/tests-main.cpp)


set_target_properties(${folder} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF
)

set(CMAKE_BUILD_TYPE Debug)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
    set_target_properties(${folder} PROPERTIES
        COMPILE_FLAGS "-Wall -Wextra -Wpedantic -Werror"
    )
endif()

# Configure to run all the tests?
if(${RUN_ALL_TESTS})
    target_compile_definitions(${folder} PRIVATE RUN_ALL_TESTS)
endif()

# Tell MSVC not to warn us about unchecked iterators in debug builds
if(${MSVC})
    set_target_properties(${folder} PROPERTIES
        COMPILE_DEFINITIONS_DEBUG _SCL_SECURE_NO_WARNINGS)
endif()

# Run the tests on every build
add_custom_target(test_${folder} ALL DEPENDS ${folder} COMMAND ${folder})

