/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Pacman
*/

#include "Pacman.hpp"

/**
 * @brief Construct a new arcade::Pacman::Pacman object
 *
 */
arcade::Pacman::Pacman() : arcade::IModule(), arcade::AGameModule() {}

/**
 * @brief Destroy the arcade::Pacman::Pacman object
 *
 */
arcade::Pacman::~Pacman() {}

/**
 * @brief initialize the game
 *
 */
void arcade::Pacman::init()
{
  arcade::IModule::GameData gameData;
  gameData.sprite_value['#'] = "assets/default/map/map1.png";
  gameData.sprite_value['P'] = "assets/default/npc/npc3.png";

  gameData.display_info = {
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', 'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
      {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
      {'#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#'},
      {'#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#'},
      {'#', ' ', ' ', '#', ' ', ' ', '#', ' ', ' ', '#'},
      {'#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#'},
      {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
      {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
  };
  this->getCoreModule()->setGameData(gameData);
  this->setTimer();
}

/**
 * @brief stop the game
 *
 */
void stop() { return; }

/**
 * @brief return the name of the game
 *
 * @return const arcade::IModule::LibName
 */
arcade::IModule::LibName arcade::Pacman::getName() const
{
  return arcade::IModule::LibName::PACMAN;
}

std::vector<std::vector<int>> arcade::Pacman::movePacman(
    std::vector<std::vector<int>> map)
{
  arcade::IModule::KeyboardInput key;

  key = this->getInput();
  printf("key: [%d]\n", key);
  switch (key) {
  case arcade::IModule::KeyboardInput::UP:
    printf("UP\n");
  }
  // if (key == arcade::IModule::KeyboardInput::UP) {
  //   if (map[this->pacman_pos.y - 1][this->pacman_pos.x] != 1)
  //     this->pacman_pos.y -= 1;
  // } else if (key == arcade::IModule::KeyboardInput::DOWN) {
  //   if (map[this->pacman_pos.y + 1][this->pacman_pos.x] != 1)
  //     this->pacman_pos.y += 1;
  // } else if (key == arcade::IModule::KeyboardInput::LEFT) {
  //   if (map[this->pacman_pos.y][this->pacman_pos.x - 1] != 1)
  //     this->pacman_pos.x -= 1;
  // } else if (key == arcade::IModule::KeyboardInput::RIGHT) {
  //   if (map[this->pacman_pos.y][this->pacman_pos.x + 1] != 1)
  //     this->pacman_pos.x += 1;
  // }
}

/**
 * @brief generate entry point for the game library
 *
 */
extern "C" arcade::Pacman *entryPoint() { return new arcade::Pacman(); }