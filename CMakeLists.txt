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
add_executable(arcade src/Main.cpp)

# Games
add_library(arcade_game SHARED lib/games/AGameModule.cpp)

add_library(arcade_snake SHARED lib/games/snake/Snake.cpp)

add_library(arcade_pacman SHARED lib/games/pacman/Pacman.cpp)

# Graphics
add_library(arcade_IDisplay SHARED lib/graphics/ADisplayModule.cpp)

add_library(
  arcade_ncurses SHARED lib/graphics/ncurses/NCurses.cpp)

add_library(arcade_sdl2 SHARED lib/graphics/sdl2/SDL2.cpp)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})


# Afterwards, link it like this
target_link_libraries(arcade PRIVATE ${CURSES_LIBRARIES})
target_link_libraries(arcade PRIVATE ${SDL2_LIBRARIES})


# Move .so files out of the build folder
set(LIB_DESTINATION ${CMAKE_SOURCE_DIR}/lib)
add_custom_command(TARGET arcade POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:arcade> ${CMAKE_SOURCE_DIR})
add_custom_command(TARGET arcade_snake POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:arcade_snake> ${LIB_DESTINATION}/arcade_snake.so)
add_custom_command(TARGET arcade_pacman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:arcade_pacman> ${LIB_DESTINATION}/arcade_pacman.so)
add_custom_command(TARGET arcade_ncurses POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:arcade_ncurses> ${LIB_DESTINATION}/arcade_ncurses.so)
add_custom_command(TARGET arcade_sdl2 POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:arcade_sdl2> ${LIB_DESTINATION}/arcade_sdl2.so)