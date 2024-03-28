add_library(arcade_sfml SHARED
    Sfml.cpp
)

target_include_directories(arcade_sfml PRIVATE
    sfml-graphics
)

target_link_libraries(arcade_sfml
    ${SFML_LIBRARIES}
)

target_link_libraries(
    arcade_sfml
    a_display_module
    games_static
    sfml-graphics
)