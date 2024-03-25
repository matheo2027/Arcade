/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2
*/

#include "Sdl2.hpp"
#include "Error.hpp"
#include <iostream>

arcade::Sdl2::Sdl2() : IModule(), ADisplayModule()
{
  this->_renderer = nullptr;
}

arcade::Sdl2::~Sdl2() {}

void arcade::Sdl2::displayMenu()
{
  SDL_Window *window = static_cast<SDL_Window *>(this->_window);
  if (window == nullptr) {
    try {
      throw NoWindowException("No window to stop");
    } catch (NoWindowException &e) {
      std::cerr << e.what() << std::endl;
    }
  }
  TTF_Font *font = static_cast<TTF_Font *>(this->_font);
  if (font == nullptr) {
    try {
      throw NoWindowException("No window to stop");
    } catch (NoWindowException &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  SDL_Color textColor = {255, 255, 255, 255}; // White color for the text

  // Function to update menu text based on selected items
  auto updateMenuText = [&]() {
    std::string menuText = "Select Graphical Library:\n";
    for (size_t i = 0; i < 3; ++i) {
      if (i == this->getCoreModule()->getMenuData().indexGraphic) {
        menuText += "-> " +
                    this->getCoreModule()->getMenuData()._graphicLibList[i] +
                    "\n";
      } else {
        menuText += "   " +
                    this->getCoreModule()->getMenuData()._graphicLibList[i] +
                    "\n";
      }
    }
    menuText += "\nSelect Game:\n";
    for (size_t i = 0; i < 2; ++i) {
      if (i == this->getCoreModule()->getMenuData().indexGame) {
        menuText +=
            "-> " + this->getCoreModule()->getMenuData()._gameLibList[i] + "\n";
      } else {
        menuText += "   " +
                    this->getCoreModule()->getMenuData()._graphicLibList[i] +
                    "\n";
      }
    }
    menuText += "\nLegend:\n";
    menuText += "Press UP/DOWN to navigate\n";
    menuText += "Press ENTER to confirm the choice\n";
    menuText +=
        "Press TAB to switch between Graphical Library and Game selection";
    return menuText;
  };

  printf("TEST TEST TEST\n");
  std::string menuText = updateMenuText();
  printf("TEST TEST TEST\n");

  SDL_Surface *textSurface =
      TTF_RenderText_Blended_Wrapped(font, menuText.c_str(), textColor, 500);
  if (textSurface == nullptr) {
    std::cerr << "Failed to create text surface: " << TTF_GetError()
              << std::endl;
    TTF_CloseFont(font);
    return;
  }

  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(this->_renderer, textSurface);
  if (textTexture == nullptr) {
    std::cerr << "Failed to create text texture: " << SDL_GetError()
              << std::endl;
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return;
  }

  int textWidth = textSurface->w;
  int textHeight = textSurface->h;
  SDL_FreeSurface(textSurface);

  // Position the menu at the top left corner
  int x = 20;
  int y = 20;

  SDL_Rect renderQuad = {x, y, textWidth, textHeight};

  int game_or_library = 0;
  // Render the menu
  while (1) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
          this->getCoreModule()->handleKeyEvent(
              arcade::IModule::KeyboardInput::UP);
          menuText = updateMenuText();
          break;
        case SDLK_DOWN:
          this->getCoreModule()->handleKeyEvent(
              arcade::IModule::KeyboardInput::DOWN);
          menuText = updateMenuText();
          break;
        case SDLK_TAB:
          this->getCoreModule()->handleKeyEvent(
              arcade::IModule::KeyboardInput::TAB);
          menuText = updateMenuText();
          break;
        case SDLK_RETURN:
          this->getCoreModule()->handleKeyEvent(
              arcade::IModule::KeyboardInput::ENTER);
          menuText = updateMenuText();
          break;
        }
      }
    }

    SDL_SetRenderDrawColor(
        this->_renderer, 30, 30, 30, 255); // Dark gray background
    SDL_RenderClear(this->_renderer);

    // Render our text
    textSurface =
        TTF_RenderText_Blended_Wrapped(font, menuText.c_str(), textColor, 500);
    textTexture = SDL_CreateTextureFromSurface(this->_renderer, textSurface);
    SDL_RenderCopy(this->_renderer, textTexture, nullptr, &renderQuad);

    SDL_RenderPresent(this->_renderer); // Update screen

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
  }
}

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
    this->displayMenu();
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
      throw SdlNotInitializedException("SDL could not initialize!\nSDL_Error:" +
                                       std::string(SDL_GetError()));
    } catch (SdlNotInitializedException &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  if (TTF_Init() == -1) {
    try {
      throw SdlTtfNotInitializedException(
          "SDL_ttf could not initialize!\nTTF Error:" +
          std::string(TTF_GetError()));
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
      throw NoWindowException("Window could not be created! SDL_Error:" +
                              std::string(SDL_GetError()) + "\n");
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

  this->_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!this->_renderer) {
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
  this->_font = font;

  // Get window surface
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  // Check if surface is null
  if (!surface) {
    try {
      throw SdlNullSurfaceException(
          "Surface could not be created! SDL_Error: " +
          std::string(SDL_GetError()));
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

  TTF_Font *font = static_cast<TTF_Font *>(this->_font);
  if (font == nullptr) {
    try {
      throw NoWindowException("No window to stop");
    } catch (NoWindowException &e) {
      std::cerr << e.what() << std::endl;
    }
  }

  // Destroy font
  TTF_CloseFont(font);
  this->_font = nullptr;

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
