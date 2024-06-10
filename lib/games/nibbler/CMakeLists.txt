add_library(arcade_nibbler SHARED
    Nibbler.cpp
)

target_link_libraries(
    arcade_nibbler
    games_static
)