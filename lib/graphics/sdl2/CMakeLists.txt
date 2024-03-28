include (FindSDL)
include (FindSDL_ttf)
include (FindSDL_image)

set(SDL_NEED_MAIN TRUE)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(arcade_sdl2 SHARED
    Sdl2.cpp
)

target_include_directories(arcade_sdl2 PRIVATE
    ${SDL2_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
)

target_link_libraries(arcade_sdl2
    ${SDL2_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
)

target_link_libraries(
    arcade_sdl2
    a_display_module
    games_static
    SDL2
    SDL2_ttf
    SDL2_image
)
