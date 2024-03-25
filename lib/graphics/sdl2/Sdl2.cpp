/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2
*/

#include "Sdl2.hpp"
#include <iostream>
#include "Error.hpp"

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
  case arcade::ADisplayModule::DisplayStatus::PAUSED:
    /* code */
    break;
  case arcade::ADisplayModule::DisplayStatus::SELECTION:
    std::cout << "Selection" << std::endl;
    /* code */
    break;
  case arcade::ADisplayModule::DisplayStatus::GAMEOVER:
    /* code */
    break;
  case arcade::ADisplayModule::DisplayStatus::WIN:
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
    try {
      throw SdlNotInitializedException("SDL could not initialize!\nSDL_Error:" + std::string(SDL_GetError()));
    } catch (SdlNotInitializedException &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  if (TTF_Init() == -1) {
    try {
      throw SdlTtfNotInitializedException("SDL_ttf could not initialize!\nTTF Error:" + std::string(TTF_GetError()));
    } catch (SdlTtfNotInitializedException &e) {
      std::cerr << e.what() << std::endl;
    }
    SDL_Quit();
    try {
      throw SdlQuitException("SDL Quit\n");
    } catch (SdlQuitException &e) {
      std::cerr << e.what() << std::endl;
    }
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
    try {
      throw NoWindowException("Window could not be created! SDL_Error:" + std::string(SDL_GetError()) + "\n");
    } catch (NoWindowException &e) {
      std::cerr << e.what() << std::endl;
    }
    SDL_Quit();
    try {
      throw SdlQuitException("SDL Quit\n");
    } catch (SdlQuitException &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError()
              << std::endl;
    this->stop();
    try {
      throw SdlQuitException("SDL Quit\n");
    } catch (SdlQuitException &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  TTF_Font *font = TTF_OpenFont("assets/default/font/font1.ttf", 24);
  if (!font) {
    std::cerr << "Failed to load font! TTF Error: " << TTF_GetError()
              << std::endl;
    this->stop();
    try {
      throw SdlQuitException("SDL Quit\n");
    } catch (SdlQuitException &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  // Get window surface
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  // Check if surface is null
  if (!surface) {
    try {
      throw SdlNullSurfaceException("Surface could not be created! SDL_Error: " + std::string(SDL_GetError()));
    } catch (SdlNullSurfaceException &e) {
      std::cerr << e.what() << std::endl;
    }
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
    try {
      throw NoWindowException("No window to stop");
    } catch (NoWindowException &e) {
      std::cerr << e.what() << std::endl;
    }
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
