/*
** EPITECH PROJECT, 2024
** bsArcade
** File description:
** ADisplayModule
*/

#ifndef ADISPLAYMODULE_HPP_
#define ADISPLAYMODULE_HPP_

#include <arcade/IDisplayModule.hpp>

namespace arcade {
class ADisplayModule : virtual public arcade::IDisplayModule {
public:
  ADisplayModule();
  ~ADisplayModule();

  arcade::GameData sendGameData();
  arcade::MenuData sendMenuData();

  void setCoreModule(arcade::CoreModule *coreModule);
  arcade::CoreModule *getCoreModule() const;

  virtual void clearWindow() = 0;
  virtual void displayWindow() = 0;
  virtual arcade::KeyboardInput getInput() = 0;
  virtual void drawSprite(std::pair<char, std::string> sprite,
                          int x,
                          int y,
                          int width,
                          int height) = 0;
  virtual void drawText(const std::string text, int x, int y, int size) = 0;
};
}; // namespace arcade

#endif /* !ADISPLAYMODULE_HPP_ */
