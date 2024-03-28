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
arcade::Snake::Snake() : arcade::IModule(), arcade::AGameModule() {}

/**
 * @brief Destroy the arcade::Snake::Snake object
 *
 */
arcade::Snake::~Snake() {}

/**
 * @brief init the game
 *
 */
void arcade::Snake::init()
{

  arcade::IModule::GameData gameData;
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
  this->getCoreModule()->setGameData(gameData);
}

/**
 * @brief stop the game
 *
 */
void arcade::Snake::stop() { return; }

/**
 * @brief return the name of the game library
 *
 * @return const arcade::IModule::LibName
 */
arcade::IModule::LibName arcade::Snake::getName() const
{
  return arcade::IModule::LibName::SNAKE;
}

/**
 * @brief generate entry point for the game library
 *
 */
extern "C" arcade::Snake *entryPoint() { return new arcade::Snake(); }