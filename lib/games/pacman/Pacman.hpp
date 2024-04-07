/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "../AGameModule.hpp"
#include <random>

namespace arcade {
class Pacman : virtual public arcade::AGameModule {
public:
  #define PACMAN 'P'
  #define GHOST 'G'
  #define COIN 'C'
  #define FOOD '*'
  #define WALL 'W'
  #define EMPTY ' '
  Pacman();
  ~Pacman();
  std::string getName();
  void init();
  void updateGame();
  void movePacman(arcade::GameData &data);
  void moveGhost(arcade::GameData &data);
  void handdleKeyEvents(arcade::KeyboardInput key);
  bool generateFood(
      std::vector<std::vector<std::pair<int, std::pair<int, int>>>> &entities);
};
}; // namespace arcade

#endif /* !PACMAN_HPP_ */
