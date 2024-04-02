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
arcade::Pacman::Pacman() : arcade::AGameModule() {}

/**
 * @brief Destroy the arcade::Pacman::Pacman object
 *
 */
arcade::Pacman::~Pacman() {}

void arcade::Pacman::init()
{
  // Initialize the game
  arcade::GameData data;
  // Define the sprite values for walls, coins, Pacman, and coins that allow Pacman to eat ghosts
  data.sprite_value['W'] = "assets/default/map/map1.png";  // Wall
  data.sprite_value['C'] = "assets/default/item/item3.png";  // Pacgum
  data.sprite_value['P'] = "assets/default/npc/npc1.png";  // Pacman
  data.sprite_value['G'] = "assets/default/npc/npc2.png";  // Ghost
  data.sprite_value[' '] = "assets/default/empty.png";  // Ghost

  data.display_info = {
    {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W', 'W', 'W', 'W', 'W', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W', ' ', ' ', ' ', 'W', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W', ' ', 'G', ' ', 'W', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'P', 'C', 'C', 'C', 'W', 'G', 'G', 'G', 'W', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W', 'W', 'W', 'W', 'W', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'C', 'W'},
    {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'}
};
  data.score = 0;
  data._description = "RULES:\n- Eat the pacgums to gain points, and eat the"
  "super pacgums to eat the ghosts\n- Don't get caught by the ghosts\nCONTROLS:"
  "\n- UP/DOWN/LEFT/RIGHT: Move";
  this->_pacman.push_back(getPacmanPos(data));
  this->getCoreModule()->setGameData(data);
  this->setDirection(arcade::KeyboardInput::RIGHT);
}

std::string arcade::Pacman::getName() { return "pacman"; }

void arcade::Pacman::updateGame()
{
  arcade::GameData data = this->getCoreModule()->getGameData();
  this->updateTimer();
  if (this->getTimer().duration.count() >= 250) {
    this->resetTimer();
    this->movePacman(data);
  }
  this->getCoreModule()->setGameData(data);
  return;
}

std::vector<std::pair<int, int>> arcade::Pacman::getPacman() const
{
  return this->_pacman;
}

void arcade::Pacman::handdleKeyEvents(arcade::KeyboardInput key)
{
  switch (key) {
    case arcade::KeyboardInput::UP:
        this->setDirection(arcade::KeyboardInput::UP);
      break;
    case arcade::KeyboardInput::DOWN:
        this->setDirection(arcade::KeyboardInput::DOWN);
      break;
    case arcade::KeyboardInput::LEFT:
        this->setDirection(arcade::KeyboardInput::LEFT);
      break;
    case arcade::KeyboardInput::RIGHT:
        this->setDirection(arcade::KeyboardInput::RIGHT);
      break;
    default:
      break;
  }
}

std::pair<int, int> arcade::Pacman::getPacmanPos(arcade::GameData &data)
{
  for (int i = 0; i < data.display_info.size(); i++) {
    for (int j = 0; j < data.display_info[i].size(); j++) {
      if (data.display_info[i][j] == PACMAN)
        return std::make_pair(i, j);
    }
  }
}

void arcade::Pacman::movePacman(arcade::GameData &data)
{
  bool is_under_pacgum_effect = false;
  std::pair<int, int> pacmanPos = getPacmanPos(data);
  std::pair<int, int> newPacmanPos = pacmanPos;

  switch (this->getDirection()) {
    case arcade::KeyboardInput::UP:
      newPacmanPos = std::make_pair(pacmanPos.first - 1, pacmanPos.second);
      this->setDirection(arcade::KeyboardInput::UP);
      break;
    case arcade::KeyboardInput::DOWN:
      newPacmanPos = std::make_pair(pacmanPos.first + 1, pacmanPos.second);
      this->setDirection(arcade::KeyboardInput::DOWN);
      break;
    case arcade::KeyboardInput::LEFT:
      newPacmanPos = std::make_pair(pacmanPos.first, pacmanPos.second - 1);
      this->setDirection(arcade::KeyboardInput::LEFT);
      break;
    case arcade::KeyboardInput::RIGHT:
      newPacmanPos = std::make_pair(pacmanPos.first, pacmanPos.second + 1);
      this->setDirection(arcade::KeyboardInput::RIGHT);
      break;
    break;
  }

  if (data.display_info[newPacmanPos.first][newPacmanPos.second] == PACGUM) {
    data.score += 10;
    data.display_info[newPacmanPos.first][newPacmanPos.second] = EMPTY;
  }

  if (data.display_info[newPacmanPos.first][newPacmanPos.second] == WALL)
    return;

  if (data.display_info[newPacmanPos.first][newPacmanPos.second] == GHOSTS) {
    this->_gameStatus = arcade::IGameModule::GAMEOVER;
    this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
    return;
  }

  for (int i = 1; i < data.display_info.size() - 1; i++) {
    for (int j = 1; j < data.display_info[i].size() - 1; j++) {
      if (data.display_info[i][j] != PACGUM && data.display_info[i][j] != GHOSTS
      && data.display_info[i][j] != WALL)
        data.display_info[i][j] = EMPTY;
    }
  }

  // Update the pacman
  this->_pacman.insert(this->_pacman.begin(), newPacmanPos);
  this->_pacman.pop_back();

  data.display_info[newPacmanPos.first][newPacmanPos.second] = PACMAN;
  return;

}

void arcade::Pacman::setPacman(std::vector<std::pair<int, int>> pacman)
{
  this->_pacman = pacman;
}

/**        break;

 * @brief generate entry point for the game library
 *
 */
extern "C" std::unique_ptr<arcade::IGameModule> entryPoint()
{
  return std::make_unique<arcade::Pacman>();
}

extern "C" arcade::ModuleType getType()
{
  return arcade::ModuleType::GAME;
}

extern "C" std::string getName()
{
  return "pacman";
}
