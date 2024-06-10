/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

/*
 * @brief Construct a new arcade::Nibbler::Nibbler object
 *
 */
arcade::Nibbler::Nibbler() : arcade::AGameModule() {}

void arcade::Nibbler::init()
{
  this->_oldDirection = arcade::KeyboardInput::RIGHT;
  arcade::GameData gameData;
  // Define the map
  std::vector<arcade::entity> mapNibbler;
  std::vector<std::vector<int>> generatedMapNibbler = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', 'F', '#', '#', '#', 'F', '#', '#', '#', 'F', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'F', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', 'F', ' ', ' ', '#', '#', '#', ' ', ' ', 'F', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', 'F', '#', '#', '#', 'F', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', 'F', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', 'F', '#', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', '#', 'F', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '-', '-', '-', 'N', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
  };

  for (int i = 0; i < generatedMapNibbler.size(); i += 1) {
    for (int j = 0; j < generatedMapNibbler[i].size(); j += 1) {
      if(generatedMapNibbler[i][j] == WALL){
      mapNibbler.push_back((arcade::entity){
          .sprite = WALL, .position = std::make_pair(j * 30, i * 30)});
      } else{
        mapNibbler.push_back((arcade::entity){
          .sprite = EMPTY, .position = std::make_pair(j * 30, i * 30)});
      }
    }
  }
  gameData.entities.push_back(mapNibbler);

  std::vector<arcade::entity> coins;
  for (int i = 0; i < generatedMapNibbler.size(); i += 1) {
    for (int j = 0; j < generatedMapNibbler[i].size(); j += 1) {
      if (generatedMapNibbler[i][j] == FOOD) {
        coins.push_back((arcade::entity){
            .sprite = FOOD, .position = std::make_pair(j * 30, i * 30)});
      }
    }
  }
  gameData.entities.push_back(coins);

  std::vector<arcade::entity> nibbler;
  nibbler.push_back(
      (arcade::entity){.sprite = HEAD, .position = std::make_pair(300, 750)});
  for (int i = 1; i < 4; i += 1) {
    nibbler.push_back((arcade::entity){
        .sprite = BODY, .position = std::make_pair(300 - (i * 30), 750)});
  }
  gameData.entities.push_back(nibbler);
  gameData.sprite_value[EMPTY] = "assets/snake/map/map1.png";
  gameData.sprite_value[WALL] = "assets/default/map/map2.png";
  gameData.sprite_value[HEAD] = "assets/snake/npc/npc1.png";
  gameData.sprite_value[BODY] = "assets/snake/npc/npc2.png";
  gameData.sprite_value[FOOD] = "assets/snake/item/item1.png";
  gameData.score = 0;
  gameData._description = "RULES:\n- Eat the gums to gain points.\n- Don't touch yourself.\nCONTROLS:"
  "\n- UP/DOWN/LEFT/RIGHT: Move";
  this->getCoreModule()->setGameData(gameData);
  this->setDirection(arcade::KeyboardInput::RIGHT);
}

static void deleteElementInLayer(std::vector<arcade::entity> &layer, int x, int y)
{
  for (int i = 0; i < layer.size(); i += 1) {
    if (layer[i].position.first == x && layer[i].position.second == y) {
      layer.erase(layer.begin() + i);
      return;
    }
  }
}

/**
 * @brief Destroy the arcade::nibbler::nibbler object
 *
 */
arcade::Nibbler::~Nibbler() {}

std::string arcade::Nibbler::getName() { return "nibbler"; }

arcade::GameData arcade::Nibbler::moveNibbler()
{
  arcade::GameData data = this->getCoreModule()->getGameData();
  bool is_eating = false;
  std::vector<arcade::entity> nibbler = data.entities[NIBBLER_LAYER];
  std::pair<int, int> head = nibbler.front().position;
  std::pair<int, int> tail = nibbler.back().position;

  // Move the nibbler
  if (this->_direction == arcade::KeyboardInput::UP && head.first % 30 == 0) {
    if (this->_oldDirection != arcade::KeyboardInput::DOWN)
      this->_oldDirection = this->_direction;
  } else if (this->_direction == arcade::KeyboardInput::DOWN &&
             head.first % 30 == 0) {
    if (this->_oldDirection != arcade::KeyboardInput::UP)
      this->_oldDirection = this->_direction;
  } else if (this->_direction == arcade::KeyboardInput::LEFT &&
             head.second % 30 == 0) {
    if (this->_oldDirection != arcade::KeyboardInput::RIGHT)
      this->_oldDirection = this->_direction;
  } else if (this->_direction == arcade::KeyboardInput::RIGHT &&
             head.second % 30 == 0) {
    if (this->_oldDirection != arcade::KeyboardInput::LEFT)
      this->_oldDirection = this->_direction;
  }

  switch (this->_oldDirection) {
  case arcade::KeyboardInput::UP:
    nibbler.front().position.second -= NIBBLER_SPEED;
    break;
  case arcade::KeyboardInput::DOWN:
    nibbler.front().position.second += NIBBLER_SPEED;
    break;
  case arcade::KeyboardInput::LEFT:
    nibbler.front().position.first -= NIBBLER_SPEED;
    break;
  case arcade::KeyboardInput::RIGHT:
    nibbler.front().position.first += NIBBLER_SPEED;
    break;
  }

  // Check if the nibbler is eating a coin
  if (getLayerCell(FOOD_LAYER, nibbler.front().position.first, nibbler.front().position.second) == FOOD){
    data.score += 10;
    deleteElementInLayer(data.entities[FOOD_LAYER], nibbler.front().position.first, nibbler.front().position.second);
    nibbler.push_back((arcade::entity){.sprite = BODY, .position = tail});
  }

  // Check if the nibbler eats itself
  for (int i = 2; i < nibbler.size(); i += 1) {
    if (nibbler[0].position == nibbler[i].position) {
      this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
      this->setGameStatus(arcade::IGameModule::GameStatus::GAMEOVER);
      return data;
    } else {
      for (int j = 1; j < nibbler.size(); j += 1) {
        switch (this->_oldDirection) {
        case arcade::KeyboardInput::UP:
          if (std::make_pair(nibbler[0].position.first,
                             nibbler[0].position.second + j) ==
              nibbler[i].position) {
      this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
            this->setGameStatus(arcade::IGameModule::GameStatus::GAMEOVER);
            return data;
          }
          break;
        case arcade::KeyboardInput::DOWN:
          if (std::make_pair(nibbler[0].position.first,
                             nibbler[0].position.second - j) ==
              nibbler[i].position) {
            this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
            this->setGameStatus(arcade::IGameModule::GameStatus::GAMEOVER);
            return data;
          }
          break;
        case arcade::KeyboardInput::LEFT:
          if (std::make_pair(nibbler[0].position.first + j,
                             nibbler[0].position.second) == nibbler[i].position) {
            this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
            this->setGameStatus(arcade::IGameModule::GameStatus::GAMEOVER);
            return data;
          }
          break;
        case arcade::KeyboardInput::RIGHT:
          if (std::make_pair(nibbler[0].position.first - j,
                             nibbler[0].position.second) == nibbler[i].position) {
            this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
            this->setGameStatus(arcade::IGameModule::GameStatus::GAMEOVER);
            return data;
          }
          break;
        }
      }
    }
  }
  // Check if the nibbler is hitting a wall
  if (this->getLayerCell(
          0, nibbler[0].position.first, nibbler[0].position.second) == WALL ||
      this->getLayerCell(0,
                         nibbler[0].position.first + (30 - NIBBLER_SPEED),
                         nibbler[0].position.second) == WALL ||
      this->getLayerCell(0,
                         nibbler[0].position.first - (30 - NIBBLER_SPEED),
                         nibbler[0].position.second) == WALL ||
      this->getLayerCell(0,
                         nibbler[0].position.first,
                         nibbler[0].position.second + (30 - NIBBLER_SPEED)) ==
          WALL ||
      this->getLayerCell(0,
                         nibbler[0].position.first,
                         nibbler[0].position.second - (30 - NIBBLER_SPEED)) ==
          WALL) {
    return data;
  }

  // update body position
  for (int i = 1; i < nibbler.size(); i++) {
    if (nibbler[i].position.first + 30 < nibbler[i - 1].position.first &&
        nibbler[i].position.second == nibbler[i - 1].position.second)
      nibbler[i].position = std::make_pair(nibbler[i].position.first + NIBBLER_SPEED,
                                         nibbler[i].position.second);
    else if (nibbler[i].position.first - 30 > nibbler[i - 1].position.first &&
             nibbler[i].position.second == nibbler[i - 1].position.second)
      nibbler[i].position = std::make_pair(nibbler[i].position.first - NIBBLER_SPEED,
                                         nibbler[i].position.second);
    else if (nibbler[i].position.second + 30 < nibbler[i - 1].position.second &&
             nibbler[i].position.first == nibbler[i - 1].position.first)
      nibbler[i].position = std::make_pair(
          nibbler[i].position.first, nibbler[i].position.second + NIBBLER_SPEED);
    else if (nibbler[i].position.second - 30 > nibbler[i - 1].position.second &&
             nibbler[i].position.first == nibbler[i - 1].position.first)
      nibbler[i].position = std::make_pair(
          nibbler[i].position.first, nibbler[i].position.second - NIBBLER_SPEED);
    else {
      if (nibbler[i - 1].position.second % 30 != 0 ||
          nibbler[i].position.first % 30 != 0) {
        if (nibbler[i].position.first < nibbler[i - 1].position.first)
          nibbler[i].position = std::make_pair(
              nibbler[i].position.first + NIBBLER_SPEED, nibbler[i].position.second);
        else
          nibbler[i].position = std::make_pair(
              nibbler[i].position.first - NIBBLER_SPEED, nibbler[i].position.second);
      } else if (nibbler[i - 1].position.first % 30 != 0 ||
                 nibbler[i].position.second % 30 != 0) {
        if (nibbler[i].position.second < nibbler[i - 1].position.second)
          nibbler[i].position = std::make_pair(
              nibbler[i].position.first, nibbler[i].position.second + NIBBLER_SPEED);
        else
          nibbler[i].position = std::make_pair(
              nibbler[i].position.first, nibbler[i].position.second - NIBBLER_SPEED);
      }
    }
  }

  data.entities[NIBBLER_LAYER] = nibbler;
  return data;
}

/**
 * @brief handle key events
 *
 * @param key
 */
void arcade::Nibbler::handdleKeyEvents(arcade::KeyboardInput key)
{
  switch (key) {
  case arcade::KeyboardInput::UP:
    if (this->getDirection() != arcade::KeyboardInput::DOWN)
      this->setDirection(arcade::KeyboardInput::UP);
    break;
  case arcade::KeyboardInput::DOWN:
    if (this->getDirection() != arcade::KeyboardInput::UP)
      this->setDirection(arcade::KeyboardInput::DOWN);
    break;
  case arcade::KeyboardInput::LEFT:
    if (this->getDirection() != arcade::KeyboardInput::RIGHT)
      this->setDirection(arcade::KeyboardInput::LEFT);
    break;
  case arcade::KeyboardInput::RIGHT:
    if (this->getDirection() != arcade::KeyboardInput::LEFT)
      this->setDirection(arcade::KeyboardInput::RIGHT);
    break;
  default:
    break;
  }
}

/**
 * @brief update the game
 *
 */
void arcade::Nibbler::updateGame()
{
  arcade::GameData data = this->getCoreModule()->getGameData();
  std::vector<arcade::timer> timers =
      this->getCoreModule()->getTimers();
  int speedVector = timers[0].duration.count() / 10;
  if (speedVector > 0)
    this->getCoreModule()->resetTimers(0);
  for (int i = 0; i < speedVector; i += 1) {
    data = this->moveNibbler();
  }
  this->getCoreModule()->setGameData(data);
}

/**
 * @brief generate entry point for the game library
 *
 */
extern "C" std::unique_ptr<arcade::IGameModule> entryPoint()
{
  return std::make_unique<arcade::Nibbler>();
}

extern "C" arcade::ModuleType getType() { return arcade::ModuleType::GAME; }

extern "C" std::string getName() { return "nibbler"; }