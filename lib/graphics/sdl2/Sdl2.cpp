/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2
*/

#include "Sdl2.hpp"
#include "Error.hpp"
#include <iostream>

arcade::Sdl2::Sdl2() : arcade::ADisplayModule()
{
  std::cout << "Sdl2 created start" << std::endl;

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
    // Fill the surface back
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
    // Update the window with the new surface
    SDL_UpdateWindowSurface(this->_window);
  }
  std::cout << "Sdl2 created finish" << std::endl;
}

arcade::Sdl2::~Sdl2()
{
  std::cout << "Sdl2 destroyed" << std::endl;
  // Destroy window
  SDL_DestroyWindow(this->_window);

  // Destroy font
  TTF_CloseFont(this->_font);

  SDL_DestroyRenderer(this->_renderer);

  IMG_Quit();

  TTF_Quit();
  // Quit SDL subsystems
  SDL_Quit();
}

/**
 * @brief clear the window
 *
 */
void arcade::Sdl2::clearWindow() { SDL_RenderClear(this->_renderer); }

/**
 * @brief draw a sprite on the window
 *
 * @param path path to the sprite
 * @param x x position of the sprite
 * @param y y position of the sprite
 * @param width width of the sprite
 * @param height height of the sprite
 */
void arcade::Sdl2::drawSprite(
    std::pair<char, std::string> sprite, int x, int y, int width, int height)
{
  x = x * width;
  y = y * height;
  SDL_Surface *surface = IMG_Load(sprite.second.c_str());
  if (surface == nullptr) {
    std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    return;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
  if (texture == nullptr) {
    std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(surface);
    return;
  }

  SDL_Rect rect = {x, y, width, height};
  SDL_RenderCopy(this->_renderer, texture, nullptr, &rect);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

/**
 * @brief draw text on the window
 *
 * @param text text to display
 * @param x x position of the text
 * @param y y position of the text
 * @param size size of the text
 */
void arcade::Sdl2::drawText(const std::string text, int x, int y, int size)
{
  SDL_Color textColor = {255, 255, 255, 255}; // White color for the text

  SDL_Surface *textSurface =
      TTF_RenderText_Blended_Wrapped(this->_font, text.c_str(), textColor, 500);
  if (textSurface == nullptr) {
    std::cerr << "Failed to create text surface: " << TTF_GetError()
              << std::endl;
    return;
  }

  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(this->_renderer, textSurface);
  if (textTexture == nullptr) {
    std::cerr << "Failed to create text texture: " << SDL_GetError()
              << std::endl;
    SDL_FreeSurface(textSurface);
    return;
  }

  int textWidth = textSurface->w;
  int textHeight = textSurface->h;
  SDL_FreeSurface(textSurface);

  SDL_Rect renderQuad = {x, y, textWidth, textHeight};
  SDL_RenderCopy(this->_renderer, textTexture, nullptr, &renderQuad);
  SDL_RenderPresent(this->_renderer);

  SDL_DestroyTexture(textTexture);
}

void arcade::Sdl2::displayWindow() { SDL_RenderPresent(this->_renderer); }

/**
 * @brief get the input from the window
 *
 * @return arcade::KeyboardInput
 */
arcade::KeyboardInput arcade::Sdl2::getInput()
{
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return arcade::KeyboardInput::CROSS;
    }
    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_UP:
        return arcade::KeyboardInput::UP;
      case SDLK_DOWN:
        return arcade::KeyboardInput::DOWN;
      case SDLK_LEFT:
        return arcade::KeyboardInput::LEFT;
      case SDLK_RIGHT:
        return arcade::KeyboardInput::RIGHT;
      case SDLK_RETURN:
        return arcade::KeyboardInput::ENTER;
      case SDLK_TAB:
        return arcade::KeyboardInput::TAB;
      case SDLK_ESCAPE:
        return arcade::KeyboardInput::ESCAPE;
      case SDLK_SPACE:
        return arcade::KeyboardInput::SPACE;
      case SDLK_a:
        return arcade::KeyboardInput::A;
      case SDLK_b:
        return arcade::KeyboardInput::B;
      case SDLK_c:
        return arcade::KeyboardInput::C;
      case SDLK_d:
        return arcade::KeyboardInput::D;
      case SDLK_e:
        return arcade::KeyboardInput::E;
      case SDLK_f:
        return arcade::KeyboardInput::F;
      case SDLK_g:
        return arcade::KeyboardInput::G;
      case SDLK_h:
        return arcade::KeyboardInput::H;
      case SDLK_i:
        return arcade::KeyboardInput::I;
      case SDLK_j:
        return arcade::KeyboardInput::J;
      case SDLK_k:
        return arcade::KeyboardInput::K;
      case SDLK_l:
        return arcade::KeyboardInput::L;
      case SDLK_m:
        return arcade::KeyboardInput::M;
      case SDLK_n:
        return arcade::KeyboardInput::N;
      case SDLK_o:
        return arcade::KeyboardInput::O;
      }
    }
  }
  return arcade::KeyboardInput::NONE;
}

/**
 * @brief entry point for the library
 *
 * @return arcade::Sdl2 *
 */
extern "C" std::unique_ptr<arcade::IDisplayModule> entryPoint()
{
  return std::make_unique<arcade::Sdl2>();
}

extern "C" arcade::ModuleType getType() { return arcade::ModuleType::GRAPHIC; }

extern "C" std::string getName() { return "sdl2"; }
