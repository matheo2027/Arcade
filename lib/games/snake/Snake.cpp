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
arcade::Snake::Snake() : arcade::AGameModule() {}

void arcade::Snake::init()
{
  int height = 21;
  int width = 21;
  arcade::GameData gameData;
  gameData.score = 0;
  gameData._description =
      "RULES:\n- Eat the food to grow\n- Don't hit the walls or "
      "yourself\nCONTROLS:\n- UP/DOWN/LEFT/RIGHT: Move";
  std::vector<std::pair<int, std::pair<int, int>>> map;
  for (int i = 0; i < height; i += 1) {
    for (int j = 0; j < width; j += 1) {
      if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
        map.push_back(std::make_pair(WALL, std::make_pair(i, j)));
      } else {
        map.push_back(std::make_pair(EMPTY, std::make_pair(i, j)));
      }
    }
  }
  gameData.entities.push_back(map);
  std::vector<std::pair<int, std::pair<int, int>>> snake;
  snake.push_back(std::make_pair(HEAD, std::make_pair(height / 2, width / 2)));
  for (int i = 1; i < 4; i += 1) {
    snake.push_back(
        std::make_pair(BODY, std::make_pair(height / 2 - i, width / 2)));
  }
  gameData.entities.push_back(snake);
  gameData.sprite_value[EMPTY] = "assets/default/map/map1.png";
  gameData.sprite_value[WALL] = "assets/default/map/map2.png";
  gameData.sprite_value[HEAD] = "assets/default/npc/npc1.png";
  gameData.sprite_value[BODY] = "assets/default/npc/npc2.png";
  gameData.sprite_value[FOOD] = "assets/default/item/item1.png";
  std::vector<std::pair<int, std::pair<int, int>>> food;
  gameData.entities.push_back(food);
  this->generateFood(gameData.entities);
  this->getCoreModule()->setGameData(gameData);
  this->setDirection(arcade::KeyboardInput::RIGHT);
}

/**
 * @brief Destroy the arcade::Snake::Snake object
 *
 */
arcade::Snake::~Snake() {}

std::string arcade::Snake::getName() { return "snake"; }

bool arcade::Snake::generateFood(
    std::vector<std::vector<std::pair<int, std::pair<int, int>>>> &entities)
{
  std::vector<std::pair<int, int>> listPossibleEmpty;
  bool is_empty = false;
  for (int i = 0; i < entities[0].size(); i += 1) {
    is_empty = true;
    if (entities[0][i].first != EMPTY) {
      is_empty = false;
    }
    for (int j = 0; j < entities[1].size(); j += 1) {
      if (entities[1][j].second == entities[0][i].second) {
        is_empty = false;
        break;
      }
    }
    listPossibleEmpty.push_back(entities[0][i].second);
  }
  if (listPossibleEmpty.empty())
    return false;
  int index = rand() % listPossibleEmpty.size();
  if (!entities[2].empty())
    entities[2].clear();
  entities[2].push_back(
      std::make_pair(FOOD,
                     std::make_pair(listPossibleEmpty[index].first,
                                    listPossibleEmpty[index].second)));
  return true;
}

void arcade::Snake::moveSnake(arcade::GameData &data)
{
  bool is_eating = false;
  std::pair<int, int> head = data.entities[1].front().second;
  std::pair<int, int> new_head = head;
  std::pair<int, int> tail = data.entities[1].back().second;

  // Move the snake
  switch (this->getDirection()) {
  case arcade::KeyboardInput::UP:
    new_head = std::make_pair(head.first, head.second - 1);
    if (data.entities[1][1].second == new_head)
      new_head = std::make_pair(head.first, head.second + 1);
    break;
  case arcade::KeyboardInput::DOWN:
    new_head = std::make_pair(head.first, head.second + 1);
    if (data.entities[1][1].second == new_head)
      new_head = std::make_pair(head.first, head.second - 1);
    break;
  case arcade::KeyboardInput::LEFT:
    new_head = std::make_pair(head.first - 1, head.second);
    if (data.entities[1][1].second == new_head)
      new_head = std::make_pair(head.first + 1, head.second);
    break;
  case arcade::KeyboardInput::RIGHT:
    new_head = std::make_pair(head.first + 1, head.second);
    if (data.entities[1][1].second == new_head)
      new_head = std::make_pair(head.first - 1, head.second);
    break;
  }

  // Check if the snake is eating a coin
  if (getLayerCell(2, new_head.first, new_head.second) == FOOD) {
    is_eating = true;
    data.entities[1].push_back(std::make_pair(BODY, tail));
    data.score += 10;
  }

  // Check if the snake is hitting a wall
  if (getLayerCell(0, new_head.first, new_head.second) == WALL ||
      getLayerCell(1, new_head.first, new_head.second) == BODY) {
    this->_gameStatus = arcade::IGameModule::GAMEOVER;
    this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
    return;
  }

  // Update the snake
  data.entities[1].front().first = BODY;
  data.entities[1].insert(data.entities[1].begin(),
                          std::make_pair(HEAD, new_head));
  data.entities[1].pop_back();

  // add a coin
  if (is_eating == true) {
    if (this->generateFood(data.entities) == false) {
      this->_gameStatus = arcade::IGameModule::WIN;
      this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
    }
  }
}

/**
 * @brief handle key events
 *
 * @param key
 */
void arcade::Snake::handdleKeyEvents(arcade::KeyboardInput key)
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
void arcade::Snake::updateGame()
{
  arcade::GameData data = this->getCoreModule()->getGameData();
  this->updateTimer();
  if (this->getTimer().duration.count() >= 500) {
    this->resetTimer();
    // Update the game
    this->moveSnake(data);
  }
  this->getCoreModule()->setGameData(data);
  return;
}

/**
 * @brief generate entry point for the game library
 *
 */
extern "C" std::unique_ptr<arcade::IGameModule> entryPoint()
{
  return std::make_unique<arcade::Snake>();
}

extern "C" arcade::ModuleType getType() { return arcade::ModuleType::GAME; }

extern "C" std::string getName() { return "snake"; }