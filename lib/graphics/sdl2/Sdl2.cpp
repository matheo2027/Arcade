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
  SDL_Color textColor = {255, 255, 255, 255}; // White color for the text

  // Function to update menu text based on selected items
  auto updateMenuText = [&]() {
    std::string menuText = "Select Graphical Library:\n";
    for (size_t i = 0;
         i < this->getCoreModule()->getMenuData()._graphicLibList.size();
         i += 1) {
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
    for (size_t i = 0;
         i < this->getCoreModule()->getMenuData()._gameLibList.size();
         i += 1) {
      if (i == this->getCoreModule()->getMenuData().indexGame) {
        menuText +=
            "-> " + this->getCoreModule()->getMenuData()._gameLibList[i] + "\n";
      } else {
        menuText +=
            "   " + this->getCoreModule()->getMenuData()._gameLibList[i] + "\n";
      }
    }
    menuText += this->getCoreModule()->getMenuData()._description;
    return menuText;
  };

  std::string menuText = updateMenuText();

  SDL_Surface *textSurface = TTF_RenderText_Blended_Wrapped(
      this->_font, menuText.c_str(), textColor, 500);
  if (textSurface == nullptr) {
    std::cerr << "Failed to create text surface: " << TTF_GetError()
              << std::endl;
    TTF_CloseFont(this->_font);
    return;
  }

  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(this->_renderer, textSurface);
  if (textTexture == nullptr) {
    std::cerr << "Failed to create text texture: " << SDL_GetError()
              << std::endl;
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(this->_font);
    return;
  }

  int textWidth = textSurface->w;
  int textHeight = textSurface->h;
  SDL_FreeSurface(textSurface);

  // Position the menu at the top left corner
  int x = 20;
  int y = 20;

  SDL_Rect renderQuad = {x, y, textWidth, textHeight};

  int running = 1;
  // Render the menu
  while (running) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        this->getCoreModule()->handleKeyEvent(
            arcade::IModule::KeyboardInput::CROSS);
        running = 0;
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
          running = 0;
        }
      }
    }

    SDL_SetRenderDrawColor(this->_renderer, 30, 30, 30, 255); // Dark gray background
    SDL_RenderClear(this->_renderer);

    // Render our text
    textSurface = TTF_RenderText_Blended_Wrapped(
        this->_font, menuText.c_str(), textColor, 500);
    textTexture = SDL_CreateTextureFromSurface(this->_renderer, textSurface);
    SDL_RenderCopy(this->_renderer, textTexture, nullptr, &renderQuad);

    SDL_RenderPresent(this->_renderer); // Update screen

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
  }
}

void arcade::Sdl2::displayGame()
{
  // Clear the screen
  SDL_SetRenderDrawColor(
      this->_renderer, 0, 0, 0, 0); // Dark gray background
  SDL_RenderClear(this->_renderer);

  // Generate the sprite map
  std::map<int, SDL_Surface *> spriteSurfaces;
  for (std::pair<int, std::string> sprite :
       this->getCoreModule()->getGameData().sprite_value) {
    spriteSurfaces[sprite.first] = IMG_Load(sprite.second.c_str());
    if (!spriteSurfaces[sprite.first]) {
      std::cerr << "Failed to load sprite: " << sprite.second << std::endl;
      return;
    }
  }

  // Get the game data
  arcade::IModule::GameData gameData = this->getCoreModule()->getGameData();

  // Update the screen
  SDL_Texture *spriteTexture = nullptr;
  SDL_Rect spriteRect;
  for (int i = 0; i < gameData.display_info.size(); i += 1) {
    for (int j = 0; j < gameData.display_info[i].size(); j += 1) {
      spriteTexture = SDL_CreateTextureFromSurface(
          this->_renderer, spriteSurfaces[gameData.display_info[i][j]]);
      if (!spriteTexture) {
        std::cerr << "Failed to create sprite texture: " << SDL_GetError()
                  << std::endl;
        return;
      }
      spriteRect = {j * 40, i * 40, 40, 40};
      if (SDL_RenderCopy(this->_renderer, spriteTexture, nullptr, &spriteRect) <
          0) {
        std::cerr << "Failed to render sprite: " << SDL_GetError() << std::endl;
        return;
      }
    }
  }

  SDL_RenderPresent(this->_renderer);

  int running = 1;
  while (running) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        this->getCoreModule()->handleKeyEvent(
            arcade::IModule::KeyboardInput::CROSS);
        running = 0;
      }
    }
  }
  SDL_DestroyTexture(spriteTexture);
}

/**
 * @brief display information on the window
 *
 */
void arcade::Sdl2::display()
{
  switch (this->getDisplayStatus()) {
  case arcade::ADisplayModule::DisplayStatus::RUNNING:
    this->displayGame();
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

  if (IMG_Init(IMG_INIT_PNG) < 0) {
    std::cerr << "SDL_image could not initialize! SDL_image Error: "
              << IMG_GetError() << std::endl;
  }

  // Create window
  this->_window = SDL_CreateWindow("Arcade",        // window title
                                   0,               // initial x position
                                   0,               // initial y position
                                   1920,            // width, in pixels
                                   1080,            // height, in pixels
                                   SDL_WINDOW_SHOWN // flags - see below
  );

  if (!this->_window) {
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

  this->_renderer =
      SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
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

  this->_font = TTF_OpenFont("assets/default/font/font1.ttf", 24);
  if (!this->_font) {
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
  SDL_Surface *surface = SDL_GetWindowSurface(this->_window);
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
    SDL_UpdateWindowSurface(this->_window);
  }
}

/**
 * @brief stop the SDL2 module and destroy the window
 *
 */
void arcade::Sdl2::stop()
{
  // Destroy window
  SDL_DestroyWindow(this->_window);
  this->_window = nullptr;

  // Destroy font
  TTF_CloseFont(this->_font);
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
