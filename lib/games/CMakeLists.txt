
add_library(games_static STATIC
    AGameModule.cpp
)

set_target_properties(games_static PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(games_static
    arcade_interfaces
)

# Include subdirectories
add_subdirectory(pacman)
add_subdirectory(snake)

# static library

# Create a shared library for games
# add_library(games SHARED "")
# target_link_libraries(games PUBLIC pacman snake)
