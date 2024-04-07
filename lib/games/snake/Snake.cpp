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
  int height = 21 * 30;
  int width = 21 * 30;
  int nb_sprite_x = width / 30;
  int nb_sprite_y = height / 30;
  this->_oldDirection = arcade::KeyboardInput::RIGHT;
  arcade::GameData gameData;
  gameData.score = 0;
  gameData._description =
      "RULES:\n- Eat the food to grow\n- Don't hit the walls or "
      "yourself\nCONTROLS:\n- UP/DOWN/LEFT/RIGHT: Move";
  std::vector<arcade::entity> map;
  for (int i = 0; i < nb_sprite_y; i += 1) {
    for (int j = 0; j < nb_sprite_x; j += 1) {
      if (i == 0 || i == nb_sprite_y - 1 || j == 0 || j == nb_sprite_x - 1) {
        map.push_back((arcade::entity){
            .sprite = WALL, .position = std::make_pair(j * 30, i * 30)});
      } else {
        map.push_back((arcade::entity){
            .sprite = EMPTY, .position = std::make_pair(j * 30, i * 30)});
      }
    }
  }
  gameData.entities.push_back(map);

  std::vector<arcade::entity> food;
  gameData.entities.push_back(food);

  std::vector<arcade::entity> snake;
  snake.push_back(
      (arcade::entity){.sprite = HEAD, .position = std::make_pair(300, 300)});
  for (int i = 1; i < 4; i += 1) {
    snake.push_back((arcade::entity){
        .sprite = BODY, .position = std::make_pair(300 - (i * 30), 300)});
  }
  gameData.entities.push_back(snake);
  gameData.sprite_value[EMPTY] = "assets/snake/map/map1.png";
  gameData.sprite_value[WALL] = "assets/default/map/map2.png";
  gameData.sprite_value[HEAD] = "assets/snake/npc/npc1.png";
  gameData.sprite_value[BODY] = "assets/snake/npc/npc2.png";
  gameData.sprite_value[FOOD] = "assets/snake/item/item1.png";
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
    std::vector<std::vector<arcade::entity>> &entities)
{
  std::vector<std::pair<int, int>> listPossibleEmpty;
  bool is_empty = false;
  for (int i = 0; i < entities[MAP_LAYER].size(); i += 1) {
    is_empty = true;
    if (entities[MAP_LAYER][i].sprite != EMPTY)
      is_empty = false;
    for (int j = 0; j < entities[SNAKE_LAYER].size(); j += 1) {
      if (entities[SNAKE_LAYER][j].position ==
          entities[MAP_LAYER][i].position) {
        is_empty = false;
        break;
      }
    }
    if (is_empty == true)
      listPossibleEmpty.push_back(entities[MAP_LAYER][i].position);
  }
  if (listPossibleEmpty.empty())
    return false;
  int index = rand() % listPossibleEmpty.size();
  if (!entities[FOOD_LAYER].empty())
    entities[FOOD_LAYER].clear();
  entities[FOOD_LAYER].push_back(
      (arcade::entity){.sprite = FOOD, .position = listPossibleEmpty[index]});
  return true;
}

arcade::GameData arcade::Snake::moveSnake()
{
  arcade::GameData data = this->getCoreModule()->getGameData();
  bool is_eating = false;
  std::vector<arcade::entity> snake = data.entities[SNAKE_LAYER];
  std::pair<int, int> head = snake.front().position;
  std::pair<int, int> tail = snake.back().position;

  // Move the snake
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
    snake.front().position.second -= SNAKE_SPEED;
    break;
  case arcade::KeyboardInput::DOWN:
    snake.front().position.second += SNAKE_SPEED;
    break;
  case arcade::KeyboardInput::LEFT:
    snake.front().position.first -= SNAKE_SPEED;
    break;
  case arcade::KeyboardInput::RIGHT:
    snake.front().position.first += SNAKE_SPEED;
    break;
  }

  // Check if the snake is eating a FOOD
  if (snake.front().position == data.entities[FOOD_LAYER].front().position) {
    is_eating = true;
    snake.push_back((arcade::entity){.sprite = BODY, .position = tail});
    data.score += 10;
  }

  // Check if the snake eats itself
  for (int i = 2; i < snake.size(); i += 1) {
    if (snake[0].position == snake[i].position) {
      this->setGameStatus(arcade::IGameModule::GameStatus::GAMEOVER);
      this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
      return data;
    } else {
      for (int j = 1; j < snake.size(); j += 1) {
        switch (this->_oldDirection) {
        case arcade::KeyboardInput::UP:
          if (std::make_pair(snake[0].position.first,
                             snake[0].position.second + j) ==
              snake[i].position) {
            this->setGameStatus(arcade::IGameModule::GameStatus::GAMEOVER);
            this->getCoreModule()->setCoreStatus(
                arcade::ICoreModule::SELECTION);
            return data;
          }
          break;
        case arcade::KeyboardInput::DOWN:
          if (std::make_pair(snake[0].position.first,
                             snake[0].position.second - j) ==
              snake[i].position) {
            this->setGameStatus(arcade::IGameModule::GameStatus::GAMEOVER);
            this->getCoreModule()->setCoreStatus(
                arcade::ICoreModule::SELECTION);
            return data;
          }
          break;
        case arcade::KeyboardInput::LEFT:
          if (std::make_pair(snake[0].position.first + j,
                             snake[0].position.second) == snake[i].position) {
            this->setGameStatus(arcade::IGameModule::GameStatus::GAMEOVER);
            this->getCoreModule()->setCoreStatus(
                arcade::ICoreModule::SELECTION);
            return data;
          }
          break;
        case arcade::KeyboardInput::RIGHT:
          if (std::make_pair(snake[0].position.first - j,
                             snake[0].position.second) == snake[i].position) {
            this->setGameStatus(arcade::IGameModule::GameStatus::GAMEOVER);
            this->getCoreModule()->setCoreStatus(
                arcade::ICoreModule::SELECTION);
            return data;
          }
          break;
        }
      }
    }
  }
  // Check if the snake is hitting a wall
  if (this->getLayerCell(
          0, snake[0].position.first, snake[0].position.second) == WALL ||
      this->getLayerCell(0,
                         snake[0].position.first + (30 - SNAKE_SPEED),
                         snake[0].position.second) == WALL ||
      this->getLayerCell(0,
                         snake[0].position.first - (30 - SNAKE_SPEED),
                         snake[0].position.second) == WALL ||
      this->getLayerCell(0,
                         snake[0].position.first,
                         snake[0].position.second + (30 - SNAKE_SPEED)) ==
          WALL ||
      this->getLayerCell(0,
                         snake[0].position.first,
                         snake[0].position.second - (30 - SNAKE_SPEED)) ==
          WALL) {
    this->_gameStatus = arcade::IGameModule::GAMEOVER;
    this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
    return data;
  }

  // update body position
  for (int i = 1; i < snake.size(); i++) {
    if (snake[i].position.first + 30 < snake[i - 1].position.first &&
        snake[i].position.second == snake[i - 1].position.second)
      snake[i].position = std::make_pair(snake[i].position.first + SNAKE_SPEED,
                                         snake[i].position.second);
    else if (snake[i].position.first - 30 > snake[i - 1].position.first &&
             snake[i].position.second == snake[i - 1].position.second)
      snake[i].position = std::make_pair(snake[i].position.first - SNAKE_SPEED,
                                         snake[i].position.second);
    else if (snake[i].position.second + 30 < snake[i - 1].position.second &&
             snake[i].position.first == snake[i - 1].position.first)
      snake[i].position = std::make_pair(
          snake[i].position.first, snake[i].position.second + SNAKE_SPEED);
    else if (snake[i].position.second - 30 > snake[i - 1].position.second &&
             snake[i].position.first == snake[i - 1].position.first)
      snake[i].position = std::make_pair(
          snake[i].position.first, snake[i].position.second - SNAKE_SPEED);
    else {
      if (snake[i - 1].position.second % 30 != 0 ||
          snake[i].position.first % 30 != 0) {
        if (snake[i].position.first < snake[i - 1].position.first)
          snake[i].position = std::make_pair(
              snake[i].position.first + SNAKE_SPEED, snake[i].position.second);
        else
          snake[i].position = std::make_pair(
              snake[i].position.first - SNAKE_SPEED, snake[i].position.second);
      } else if (snake[i - 1].position.first % 30 != 0 ||
                 snake[i].position.second % 30 != 0) {
        if (snake[i].position.second < snake[i - 1].position.second)
          snake[i].position = std::make_pair(
              snake[i].position.first, snake[i].position.second + SNAKE_SPEED);
        else
          snake[i].position = std::make_pair(
              snake[i].position.first, snake[i].position.second - SNAKE_SPEED);
      }
    }
  }

  // add a food if the snake is eating
  if (is_eating == true) {
    if (this->generateFood(data.entities) == false) {
      this->_gameStatus = arcade::IGameModule::WIN;
      this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
    }
  }
  data.entities[SNAKE_LAYER] = snake;
  return data;
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
  std::vector<arcade::ICoreModule::timer> timers =
      this->getCoreModule()->getTimers();
  int speedVector = timers[0].duration.count() / 10;
  if (speedVector > 0)
    this->getCoreModule()->resetTimers(0);
  for (int i = 0; i < speedVector; i += 1) {
    data = this->moveSnake();
  }
  this->getCoreModule()->setGameData(data);
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