cmake_minimum_required(VERSION 3.10)
project(games)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include subdirectories
add_subdirectory(pacman)
add_subdirectory(snake)

# Create a shared library for games
add_library(games SHARED "")
target_link_libraries(games PUBLIC pacman snake)

# Move the .so file to the root of the lib folder
set_target_properties(games PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib)
