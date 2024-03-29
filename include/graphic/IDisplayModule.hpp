/*
** EPITECH PROJECT, 2024
** bsArcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include "Arcade.hpp"
#include "CoreModule.hpp"
namespace arcade {
class CoreModule;
class IDisplayModule {
public:
  IDisplayModule(){};
  virtual ~IDisplayModule(){};

  virtual std::string getName() = 0;

  virtual void setCoreModule(arcade::CoreModule *coreModule) = 0;
  virtual arcade::CoreModule *getCoreModule() const = 0;

  virtual void clearWindow() = 0;
  virtual void displayWindow() = 0;
  virtual arcade::KeyboardInput getInput() = 0;
  virtual void
  drawSprite(std::pair<char, std::string> sprite, int x, int y, int width, int height) = 0;
  virtual void drawText(const std::string text, int x, int y, int size) = 0;

protected:
  arcade::CoreModule *_coreModule;
};
}; // namespace arcade

#endif /* !IDISPLAYMODULE_HPP_ */
