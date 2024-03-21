/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "IGameModule.hpp"

namespace arcade {
class Pacman : virtual public arcade::IGameModule {
public:
  Pacman();
  ~Pacman();

protected:
private:
};
}; // namespace arcade

#endif /* !PACMAN_HPP_ */
