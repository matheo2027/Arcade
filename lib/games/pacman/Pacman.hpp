/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
#define PACMAN_HPP_

#include "../AGameModule.hpp"

namespace arcade {
class Pacman : virtual public arcade::AGameModule {
public:
  #define WALL 'W'
  #define EMPTY ' '
  #define GHOSTS 'G'
  #define PACMAN 'P'
  #define PACGUM 'C'

  Pacman();
  ~Pacman();
  std::string getName();
  void init();
  void updateGame();
  void handdleKeyEvents(arcade::KeyboardInput key);
  void movePacman(arcade::GameData &data);
  std::vector<std::pair<int, int>> getPacman() const;
  void setPacman(std::vector<std::pair<int, int>> pacman);
  std::pair<int, int> getPacmanPos(arcade::GameData &data);

protected:
  std::vector<std::pair<int, int>> _pacman;
  std::vector<std::pair<int, int>> _ghost;
  std::vector<std::pair<int, int>> _pacgum;
};
}; // namespace arcade

#endif /* !PACMAN_HPP_ */
