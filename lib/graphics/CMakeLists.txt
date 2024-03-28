# Include subdirectories

add_library(ADisplayModule STATIC
    ADisplayModule.cpp
)

target_link_libraries(ADisplayModule
    ArcadeInterfaces
)

#add_library(graphics STATIC ADisplayModule.cpp ADisplayModule.hpp)

# Create a shared library for graphics
# add_custom_target(graphics_module DEPENDS Sdl2 NCurses Sfml)
#add_library(graphics SHARED "")
#target_link_libraries(graphics Sdl2 NCurses Sfml)

add_subdirectory(sdl2)
add_subdirectory(ncurses)
# add_subdirectory(sfml)
