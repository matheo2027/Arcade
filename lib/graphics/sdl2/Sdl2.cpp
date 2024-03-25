/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2
*/

#include "Sdl2.hpp"
#include <iostream>

arcade::Sdl2::Sdl2() : IModule(), ADisplayModule()
{
  this->_renderer = nullptr;
}

arcade::Sdl2::~Sdl2() {}

/**
 * @brief display information on the window
 *
 */
void arcade::Sdl2::display()
{
  switch (this->getDisplayStatus()) {
  case arcade::ADisplayModule::DisplayStatus::RUNNING:
    /* code */
    break;

  default:
    break;
  }
}

/**
 * @brief initailize the SDL2 module and create a window
 *
 */
void arcade::Sdl2::init()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    throw std::exception();
  }

  if (TTF_Init() == -1) {
    std::cerr << "SDL_ttf could not initialize! TTF Error: " << TTF_GetError()
              << std::endl;
    SDL_Quit();
    throw std::exception();
  }

  // Create window
  SDL_Window *window = SDL_CreateWindow("Arcade",        // window title
                                        0,               // initial x position
                                        0,               // initial y position
                                        1920,            // width, in pixels
                                        1080,            // height, in pixels
                                        SDL_WINDOW_SHOWN // flags - see below
  );

  if (!window) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    throw std::exception();
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError()
              << std::endl;
    this->stop();
    throw std::exception();
  }

  TTF_Font *font = TTF_OpenFont("assets/default/font/font1.ttf", 24);
  if (!font) {
    std::cerr << "Failed to load font! TTF Error: " << TTF_GetError()
              << std::endl;
    this->stop();
    throw std::exception();
  }

  // Get window surface
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  // Check if surface is null
  if (!surface) {
    std::cerr << "Could not get window surface! SDL_Error: " << SDL_GetError()
              << std::endl;
    throw std::exception();
  } else {
    // Fill the surface white
    SDL_FillRect(surface,
                 NULL,
                 SDL_MapRGB(surface->format, 0, 0, 0)); // RGB value for black
    // Update the window with the new surface
    SDL_UpdateWindowSurface(window);
  }

  this->_window = window; // Save window in the class
}

/**
 * @brief stop the SDL2 module and destroy the window
 *
 */
void arcade::Sdl2::stop()
{
  SDL_Window *window = static_cast<SDL_Window *>(this->_window);
  if (window == nullptr) {
    throw std::exception();
  }

  // Destroy window
  SDL_DestroyWindow(window);

  this->_window = nullptr;

  if (this->_renderer)
    SDL_DestroyRenderer(this->_renderer);
  TTF_Quit();
  // Quit SDL subsystems
  SDL_Quit();
}

/**
 * @brief return the name of the module
 *
 * @return arcade::IModule::LibName
 */
arcade::IModule::LibName arcade::Sdl2::getName() const
{
  return arcade::IModule::LibName::SDL;
}

/**
 * @brief entry point for the library
 *
 * @return arcade::Sdl2 *
 */
extern "C" arcade::Sdl2 *entryPoint() { return new arcade::Sdl2(); }
