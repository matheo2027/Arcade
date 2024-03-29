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
  arcade::GameData gameData;
  int height = 21;
  int width = 21;
  for (int i = 0; i < height; i += 1) {
    gameData.display_info.push_back(std::vector<int>(width));
    for (int j = 0; j < width; j += 1) {
      if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
        gameData.display_info[i][j] = WALL;
      } else {
        gameData.display_info[i][j] = EMPTY;
      }
    }
  }
  gameData.display_info[height / 2][width / 2] = HEAD;
  this->_snake.push_back(std::make_pair(height / 2, width / 2));
  for (int i = 1; i < 4; i += 1) {
    gameData.display_info[height / 2][width / 2 + i] = BODY;
    this->_snake.push_back(std::make_pair(height / 2, width / 2 + i));
  }
  gameData.sprite_value[EMPTY] = "assets/default/map/map1.png";
  gameData.sprite_value[WALL] = "assets/default/map/map2.png";
  gameData.sprite_value[HEAD] = "assets/default/npc/npc1.png";
  gameData.sprite_value[BODY] = "assets/default/npc/npc2.png";
  gameData.sprite_value[FOOD] = "assets/default/item/item1.png";
  this->generateFood(gameData.display_info);
  this->getCoreModule()->setGameData(gameData);
  this->setDirection(arcade::KeyboardInput::RIGHT);
}

/**
 * @brief Destroy the arcade::Snake::Snake object
 *
 */
arcade::Snake::~Snake() {}

std::string arcade::Snake::getName() { return "snake"; }

void arcade::Snake::generateFood(std::vector<std::vector<int>> &display_info)
{
  int x = rand() % 20;
  int y = rand() % 20;
  while (display_info[x][y] != EMPTY) {
    x = rand() % 20;
    y = rand() % 20;
  }
  display_info[x][y] = FOOD;
}

std::vector<std::vector<int>>
arcade::Snake::moveSnake(std::vector<std::vector<int>> display_info)
{
  bool is_eating = false;
  std::pair<int, int> head = this->_snake[0];
  std::pair<int, int> new_head = head;
  std::pair<int, int> tail = this->_snake[this->_snake.size() - 1];

  // Move the snake
  switch (this->getDirection()) {
  case arcade::KeyboardInput::UP:
    new_head = std::make_pair(head.first - 1, head.second);
    break;
  case arcade::KeyboardInput::DOWN:
    new_head = std::make_pair(head.first + 1, head.second);
    break;
  case arcade::KeyboardInput::LEFT:
    new_head = std::make_pair(head.first, head.second - 1);
    break;
  case arcade::KeyboardInput::RIGHT:
    new_head = std::make_pair(head.first, head.second + 1);
    break;
  }

  // Check if the snake is eating a coin
  if (display_info[new_head.first][new_head.second] == FOOD) {
    is_eating = true;
    this->_snake.push_back(tail);
  }
  // Check if the snake is eating itself
  // for (int i = 1; i < snake.size(); i++) {
  //   if (new_head == snake[i]) {
  //     this->getCoreModule()->getGraphicModule()->setDisplayStatus(arcade::ADisplayModule::DisplayStatus::GAMEOVER);
  //     return display_info;
  //   }
  // }

  // Check if the snake is hitting a wall
  if (display_info[new_head.first][new_head.second] == WALL) {
    return display_info;
  }

  // clear the map
  for (int i = 1; i < display_info.size() - 1; i++) {
    for (int j = 1; j < display_info[i].size() - 1; j++) {
      if (display_info[i][j] != FOOD)
        display_info[i][j] = EMPTY;
    }
  }

  // Update the snake
  this->_snake.insert(this->_snake.begin(), new_head);
  this->_snake.pop_back();

  // Update the map
  for (int i = 0; i < this->_snake.size(); i++) {
    if (i == 0)
      display_info[this->_snake[i].first][this->_snake[i].second] = HEAD;
    else
      display_info[this->_snake[i].first][this->_snake[i].second] = BODY;
  }

  // add a coin
  if (is_eating == true) {
    this->generateFood(display_info);
  }

  return display_info;
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
    data.display_info = this->moveSnake(data.display_info);
  }
  this->getCoreModule()->setGameData(data);
  return;
}

/**
 * @brief get the snake
 *
 * @return std::vector<std::pair<int, int>>
 */
std::vector<std::pair<int, int>> arcade::Snake::getSnake() const
{
  return this->_snake;
}

/**
 * @brief set the snake
 *
 * @param snake
 */
void arcade::Snake::setSnake(std::vector<std::pair<int, int>> snake)
{
  this->_snake = snake;
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