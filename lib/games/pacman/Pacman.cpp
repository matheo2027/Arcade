/*
** EPITECH PROJECT, 2024
** $
** File description:
** pacman
*/

#include "Pacman.hpp"

/**
 * @brief Construct a new arcade::Pacman::Pacman object
 *
 */
arcade::Pacman::Pacman() : arcade::AGameModule() {}

void arcade::Pacman::init()
{
  int height = 21;
  int width = 21;
  arcade::GameData gameData;
  gameData.score = 0;
  gameData._description =
      "RULES:\n- Eat the food and the ghosts\n- Don't be eat by the ghosts"
      "\nCONTROLS:\n- UP/DOWN/LEFT/RIGHT: Move";
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
  std::vector<std::pair<int, std::pair<int, int>>> pacman;
  pacman.push_back(std::make_pair(PACMAN, std::make_pair(height / 2, width / 1.25)));
  for (int i = 1; i < 1; i += 1) {
    pacman.push_back(
        std::make_pair(PACMAN, std::make_pair(height / 2 - i, width / 1.25)));
  }
  gameData.entities.push_back(pacman);
  std::vector<std::pair<int, std::pair<int, int>>> ghost;
  ghost.push_back(std::make_pair(GHOST, std::make_pair(height / 2, width / 2)));
  gameData.entities.push_back(ghost);
  gameData.sprite_value[EMPTY] = "assets/default/map/map7.png";
  gameData.sprite_value[WALL] = "assets/default/map/map7.png";
  gameData.sprite_value[COIN] = "assets/default/item/item6.png";
  gameData.sprite_value[PACMAN] = "assets/default/npc/npc4.png";
  gameData.sprite_value[GHOST] = "assets/default/npc/npc5.png";
  gameData.sprite_value[FOOD] = "assets/default/item/item3.png";
  std::vector<std::pair<int, std::pair<int, int>>> food;
  gameData.entities.push_back(food);
  this->generateFood(gameData.entities);
  this->getCoreModule()->setGameData(gameData);
  this->setDirection(arcade::KeyboardInput::RIGHT);
}

/**
 * @brief Destroy the arcade::Pacman::Pacman object
 *
 */
arcade::Pacman::~Pacman() {}

std::string arcade::Pacman::getName() { return "pacman"; }

bool arcade::Pacman::generateFood(
    std::vector<std::vector<std::pair<int, std::pair<int, int>>>> &entities)
{
  std::vector<std::pair<int, int>> listPossibleEmpty;

  // Remplir listPossibleEmpty avec les cases vides
  for (int i = 0; i < entities[0].size(); i++) {
    bool is_empty = true;

    // Vérifier si la case est vide
    if (entities[0][i].first != EMPTY)
      is_empty = false;

    // Vérifier si la case est dans le carré de 3 par 6 au milieu de la map
    for (int j = 0; j < entities[1].size(); j++) {
      if (entities[1][j].second == entities[0][i].second) {
        is_empty = false;
        break;
      }
    }

    // Si la case est vide, l'ajouter à listPossibleEmpty
    if (is_empty)
      listPossibleEmpty.push_back(entities[0][i].second);
  }

  // Si aucune case vide n'est disponible, retourner false
  if (listPossibleEmpty.empty())
    return false;

  // Effacer les éléments précédents de la couche de la nourriture
  entities[2].clear();

  // Placer la nourriture dans toutes les cases vides disponibles
  for (const auto& empty_pos : listPossibleEmpty) {
    entities[2].push_back(
        std::make_pair(FOOD, std::make_pair(empty_pos.first, empty_pos.second)));
  }

  return true;
}

void arcade::Pacman::movePacman(arcade::GameData &data)
{
  bool is_eating = false;
  std::pair<int, int> head = data.entities[1].front().second;
  std::pair<int, int> new_head = head;
  std::pair<int, int> tail = data.entities[1].back().second;

  // Move the pacman
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

  // Check if the pacman is eating food
  if (getLayerCell(2, new_head.first, new_head.second) == FOOD) {
    is_eating = true;
    data.score += 10;
  }

  // Check if the pacman is hitting a wall
  if (getLayerCell(0, new_head.first, new_head.second) == WALL) {
    return;
  }

  // Update the pacman
  data.entities[1].front().first = PACMAN;
  data.entities[1].insert(data.entities[1].begin(),
                          std::make_pair(PACMAN, new_head));
  data.entities[1].pop_back();

  // add a coin
  if (is_eating == true) {
    if (this->generateFood(data.entities) == false) {
      this->_gameStatus = arcade::IGameModule::WIN;
      this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
    }
  }
}

void arcade::Pacman::moveGhost(arcade::GameData &data)
{
  std::pair<int, int> head = data.entities[2].front().second;
  std::pair<int, int> new_head = head;

  // Generate a random direction
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 3);
  int random_direction = dis(gen);

  // Move the ghost randomly
  switch (random_direction) {
  case 0: // UP
    new_head = std::make_pair(head.first, head.second - 1);
    if (data.entities[2][1].second == new_head)
      new_head = std::make_pair(head.first, head.second + 1);
    break;
  case 1: // DOWN
    new_head = std::make_pair(head.first, head.second + 1);
    if (data.entities[2][1].second == new_head)
      new_head = std::make_pair(head.first, head.second - 1);
    break;
  case 2: // LEFT
    new_head = std::make_pair(head.first - 1, head.second);
    if (data.entities[2][1].second == new_head)
      new_head = std::make_pair(head.first + 1, head.second);
    break;
  case 3: // RIGHT
    new_head = std::make_pair(head.first + 1, head.second);
    if (data.entities[2][1].second == new_head)
      new_head = std::make_pair(head.first - 1, head.second);
    break;
  }

  // Check if the ghost is hitting a wall
  if (getLayerCell(0, new_head.first, new_head.second) == WALL) {
    return;
  }

  // Update the ghost's position in the game data
  data.entities[2].front().first = GHOST;
  data.entities[2].front().second = new_head;
}


/**
 * @brief handle key events
 *
 * @param key
 */
void arcade::Pacman::handdleKeyEvents(arcade::KeyboardInput key)
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
void arcade::Pacman::updateGame()
{
  arcade::GameData data = this->getCoreModule()->getGameData();
  this->updateTimer();
  if (this->getTimer().duration.count() >= 500) {
    this->resetTimer();
    // Update the game
    this->movePacman(data);
    this->moveGhost(data);
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
  return std::make_unique<arcade::Pacman>();
}

extern "C" arcade::ModuleType getType() { return arcade::ModuleType::GAME; }

extern "C" std::string getName() { return "pacman"; }