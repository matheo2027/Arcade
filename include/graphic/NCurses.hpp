/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCurses
*/

#ifndef NCURSES_HPP_
#define NCURSES_HPP_

#include "IDisplayModule.hpp"

namespace arcade {
class NCurses : virtual public arcade::IDisplayModule {
public:
  NCurses();
  ~NCurses();

protected:
private:
};
}; // namespace arcade

#endif /* !NCURSES_HPP_ */
