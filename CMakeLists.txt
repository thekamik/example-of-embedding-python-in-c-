cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Python VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add an executable target
add_executable(main
    src/main.cpp
)

# Include directories
target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/python-3.13.0-embed-amd64
)

# Link the Python library
target_link_libraries(main PRIVATE
    ${PROJECT_SOURCE_DIR}/python-3.13.0-embed-amd64/python313.dll
)

# Copy the scripts folder to the build directory after building
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts"
    "$<TARGET_FILE_DIR:main>/scripts"
)
