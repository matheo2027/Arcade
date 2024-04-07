/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "../AGameModule.hpp"

namespace arcade {
class Snake : virtual public arcade::AGameModule {
public:
#define HEAD 'P'
#define BODY '*'
#define FOOD 'F'
#define WALL '#'
#define EMPTY ' '
#define SNAKE_SPEED 1
#define MAP_LAYER 0
#define FOOD_LAYER 1
#define SNAKE_LAYER 2
  Snake();
  ~Snake();
  std::string getName();
  void init();
  void updateGame();
  arcade::GameData moveSnake();
  void handdleKeyEvents(arcade::KeyboardInput key);
  bool generateFood(std::vector<std::vector<arcade::entity>> &entities);
};
}; // namespace arcade

#endif /* !SNAKE_HPP_ */
