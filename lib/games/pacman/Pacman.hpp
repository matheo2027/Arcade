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
  #define WALL '#'
  #define EMPTY ' '
  #define GHOSTS 'G'
  #define SCAREDGHOSTS 'S'
  #define PACMAN 'P'
  #define COIN '*'
  #define SUPERPACGUM 'F'
  #define PACMAN_START std::make_pair(300, 360)
  #define GHOST_START_1 std::make_pair(270, 270)
  #define GHOST_START_2 std::make_pair(270, 300)
  #define GHOST_START_3 std::make_pair(330, 270)
  #define GHOST_START_4 std::make_pair(330, 300)
  #define MAP_LAYER 0
  #define COIN_LAYER 1
  #define PACMAN_LAYER 2
  #define GHOSTS_LAYER 3
  #define GHOSTS_DEATH 'D'

  enum ghostState {HUNTING, FEAR, DEATH};

  struct ghost {
    std::pair<int, int> destination;
    arcade::KeyboardInput direction;
  };


  Pacman();
  ~Pacman();
  std::string getName();
  void init();
  void updateGame();
  void handdleKeyEvents(arcade::KeyboardInput key);
  arcade::GameData movePacman(arcade::GameData &data);
  arcade::GameData moveGhosts(arcade::GameData &data);
  bool isGhostsHittingWall(arcade::entity ghosts);

protected:
  std::vector<ghost> _ghost;
  ghostState _ghostState;
  int _ghostspeed;
  int _gameSpeed;

};
}; // namespace arcade

#endif /* !PACMAN_HPP_ */
