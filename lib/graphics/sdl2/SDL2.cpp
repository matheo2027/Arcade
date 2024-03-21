/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2
*/

#include "SDL2.hpp"
#include <iostream>

arcade::SDL2::SDL2() : IModule(), ADisplayModule() {}

arcade::SDL2::~SDL2() {}

void arcade::SDL2::init()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    throw std::exception();
  }

  // Create window
  SDL_Window *window =
      SDL_CreateWindow("Arcade",                // window title
                       SDL_WINDOWPOS_UNDEFINED, // initial x position
                       SDL_WINDOWPOS_UNDEFINED, // initial y position
                       640,                     // width, in pixels
                       480,                     // height, in pixels
                       SDL_WINDOW_SHOWN         // flags - see below
      );

  if (!window) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    throw std::exception();
  }
}

void arcade::SDL2::stop() {}