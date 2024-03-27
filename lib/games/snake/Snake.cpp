/*
** EPITECH PROJECT, 2024
** $
** File description:
** Snake
*/

#include "Snake.hpp"

/**
 * @brief Construct a new arcade::Snake::Snake object
 *
 */
arcade::Snake::Snake() : arcade::AGameModule()
{
  arcade::GameData gameData;
  int height = 27;
  int width = 48;
  for (int i = 0; i < height; i++) {
    gameData.display_info.push_back(std::vector<int>(width));
    for (int j = 0; j < width; j++) {
      if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
        gameData.display_info[i][j] = '#';
      else
        gameData.display_info[i][j] = ' ';
    }
  }
  gameData.display_info[height / 2][width / 2] = 'P';
  gameData.display_info[height / 2][width / 2 + 1] = '-';
  gameData.display_info[height / 2][width / 2 + 2] = '-';
  gameData.display_info[height / 2][width / 2 + 3] = '-';
  gameData.sprite_value[' '] = "assets/default/map/map1.png";
  gameData.sprite_value['#'] = "assets/default/map/map2.png";
  gameData.sprite_value['P'] = "assets/default/npc/npc1.png";
  gameData.sprite_value['-'] = "assets/default/npc/npc2.png";
}

/**
 * @brief Destroy the arcade::Snake::Snake object
 *
 */
arcade::Snake::~Snake() {}

/**
 * @brief generate entry point for the game library
 *
 */
extern "C" std::unique_ptr<arcade::IGameModule> entryPoint()
{
  return std::make_unique<arcade::Snake>();
}

extern "C" arcade::ModuleType getType()
{
  return arcade::ModuleType::GAME;
}

extern "C" std::string getName() { return "snake"; }