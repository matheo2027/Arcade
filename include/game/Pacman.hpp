/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "AGameModule.hpp"

namespace arcade {
class Pacman : virtual public arcade::AGameModule {
public:
  Pacman();
  ~Pacman();
  void init();
  void stop(){};
  arcade::IModule::LibName getName() const;

  std::vector<std::vector<int>> movePacman(std::vector<std::vector<int>>);

  enum Direction { UP, DOWN, LEFT, RIGHT };

  struct PacmanPos {
    int x;
    int y;
    Direction direction;
  };

protected:
private:
};
}; // namespace arcade

#endif /* !PACMAN_HPP_ */
