cmake_minimum_required(VERSION 3.10)
project(graphics)

# Set C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include subdirectories
add_subdirectory(sdl2)
add_subdirectory(ncurses)

# Create a shared library for graphics
add_library(graphics SHARED "")
target_link_libraries(graphics PUBLIC SDL2 NCurses)

# Move the .so file to the root of the lib folder
set_target_properties(graphics PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib)
