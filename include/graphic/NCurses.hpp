/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "ADisplayModule.hpp"
#include <ncurses.h>

namespace arcade {
class NCurses : virtual public arcade::ADisplayModule {
public:
  NCurses();
  ~NCurses();
  void display();
  void displayMenu();
  void displayGame();

protected:
  WINDOW *_window;
};
}; // namespace arcade

#endif /* !NCURSES_HPP_ */
