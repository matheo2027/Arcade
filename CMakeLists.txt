cmake_minimum_required(VERSION 3.10)

project(
  Arcade
  VERSION 0.1
  DESCRIPTION "Arcade Game Engine"
  LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-gnu-unique")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/graphic)
include_directories(${CMAKE_SOURCE_DIR}/include/game)

# Main arcade executable
add_executable(arcade src/main.cpp) # Add other source files as needed

# Games
add_library(arcade_game SHARED games/IGameModule.cpp) # Add other source files
                                                       # as needed

add_library(arcade_snake SHARED games/snake/Snake.cpp) # Add other source files
                                                       # as needed

add_library(arcade_pacman SHARED games/pacman/Pacman.cpp) # Add other source
                                                          # files as needed

# Graphics
add_library(arcade_graphic SHARED graphics/IDisplayModule.cpp) # Add other source files
                                                       # as needed
add_library(
  arcade_ncurses SHARED graphics/ncurses/NCurses.cpp) # Add other source files
                                                      # as needed
add_library(arcade_sdl2 SHARED graphics/sdl2/SDL2.cpp) # Add other source files
                                                       # as needed

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})


# Afterwards, link it like this
target_link_libraries(arcade PRIVATE ${CURSES_LIBRARIES})
target_link_libraries(arcade PRIVATE ${SDL2_LIBRARIES})
