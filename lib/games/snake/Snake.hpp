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
#define BODY '-'
#define FOOD 'C'
#define WALL '#'
#define EMPTY ' '
  Snake();
  ~Snake();
  std::string getName();
  void init();
  void updateGame();
  void moveSnake(arcade::GameData &data);
  void handdleKeyEvents(arcade::KeyboardInput key);
  bool generateFood(
      std::vector<std::vector<std::pair<int, std::pair<int, int>>>> &entities);
};
}; // namespace arcade

#endif /* !SNAKE_HPP_ */
