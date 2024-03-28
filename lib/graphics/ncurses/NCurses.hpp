/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "../ADisplayModule.hpp"
#include <ncurses.h>

namespace arcade {
class NCurses : virtual public arcade::ADisplayModule {
public:
  NCurses();
  ~NCurses();
  void clearWindow();
  void displayWindow();
  arcade::KeyboardInput getInput();
  void drawText(const std::string text, int x, int y, int size);
  void drawSprite(
      std::pair<char, std::string> sprite, int x, int y, int width, int height);

protected:
  WINDOW *_window;
};
}; // namespace arcade

#endif /* !NCURSES_HPP_ */
