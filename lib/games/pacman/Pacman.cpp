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

  //Ghosts clock
  std::vector<arcade::timer> timers =  this->getCoreModule()->getTimers();
  timers.push_back({std::chrono::steady_clock::now(),
                           std::chrono::steady_clock::now(),
                           std::chrono::milliseconds(0)});
  // Ghost unlock
  timers.push_back({std::chrono::steady_clock::now(),
                           std::chrono::steady_clock::now(),
                           std::chrono::milliseconds(0)});
  // Ghost fear clock
  timers.push_back({std::chrono::steady_clock::now(),
                           std::chrono::steady_clock::now(),
                           std::chrono::milliseconds(0)});
  this->getCoreModule()->setTimers(timers);


  arcade::GameData data;
  // Define the sprite values for walls, coins, Pacman, and coins that allow Pacman to eat ghosts
  data.sprite_value[WALL] = "assets/default/map/map1.png";  // Wall
  data.sprite_value[COIN] = "assets/default/item/item3.png";  // Coin
  data.sprite_value[SUPERPACGUM] = "assets/default/item/item2.png";  // SuperPacgum
  data.sprite_value[PACMAN] = "assets/default/npc/npc1.png";  // Pacman
  data.sprite_value[GHOSTS] = "assets/default/npc/npc2.png";  // Ghost
  data.sprite_value[SCAREDGHOSTS] = "assets/default/npc/npc3.png";  // ScaredGhost
  data.sprite_value[EMPTY] = "assets/default/map/map2.png";  // Empty
  data.sprite_value[GHOSTS_DEATH] = "assets/default/eyes.png";  // Death

  // Define the map
  std::vector<arcade::entity> map;
  std::vector<std::vector<int>> generatedMap = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', ' ', '#'},
    {'#', ' ', '#', '#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', ' ', '#'},
    {'#', ' ', 'F', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'F', ' ', '#'},
    {'#', ' ', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', ' ', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', '#', '#', '#', '#'},
    {'#', '#', '#', '#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', '#', '#', '#'},
    {'#', '#', '#', '#', ' ', '#', '#', ' ', '#', 'G', 'G', 'G', '#', ' ', '#', '#', ' ', '#', '#', '#', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'G', 'G', 'G', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'#', '#', '#', '#', ' ', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', '#', '#', '#'},
    {'#', '#', '#', '#', ' ', '#', ' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ', ' ', '#', ' ', '#', '#', '#', '#'},
    {'#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', ' ', '#'},
    {'#', ' ', 'F', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'F', ' ', '#'},
    {'#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

  for (int i = 0; i < generatedMap.size(); i += 1) {
    for (int j = 0; j < generatedMap[i].size(); j += 1) {
      if(generatedMap[i][j] == WALL){
      map.push_back((arcade::entity){
          .sprite = WALL, .position = std::make_pair(j * 30, i * 30)});
      } else{
        map.push_back((arcade::entity){
          .sprite = EMPTY, .position = std::make_pair(j * 30, i * 30)});
      }
    }
  }
  data.entities.push_back(map);

  std::vector<arcade::entity> coins;
  for (int i = 0; i < generatedMap.size(); i += 1) {
    for (int j = 0; j < generatedMap[i].size(); j += 1) {
      if (generatedMap[i][j] == EMPTY) {
        coins.push_back((arcade::entity){
            .sprite = COIN, .position = std::make_pair(j * 30, i * 30)});
      }
      if(generatedMap[i][j] == SUPERPACGUM){
        coins.push_back((arcade::entity){
                  .sprite = SUPERPACGUM, .position = std::make_pair(j * 30, i * 30)});
      }
    }
  }
  data.entities.push_back(coins);

  data.entities.push_back({(arcade::entity){.sprite = PACMAN, .position = PACMAN_START}});

  arcade::entity ghost1 = {(arcade::entity){.sprite = GHOSTS, .position = GHOST_START_1}};
  arcade::entity ghost2 = {(arcade::entity){.sprite = GHOSTS, .position = GHOST_START_2}};
  arcade::entity ghost3 = {(arcade::entity){.sprite = GHOSTS, .position = GHOST_START_3}};
  arcade::entity ghost4 = {(arcade::entity){.sprite = GHOSTS, .position = GHOST_START_4}};
  data.entities.push_back({ghost1, ghost2, ghost3, ghost4});
  this->_gameSpeed = 1;

  for (int i = 0; i < data.entities[GHOSTS_LAYER].size(); i += 1){
    this->_ghost.push_back((ghost){.destination=PACMAN_START});
  }
  this->_ghostspeed = this->_gameSpeed;
  this->_ghostState = HUNTING;

  data.score = 0;
  data._description = "RULES:\n- Eat the pacgums to gain points, and eat the"
  "super pacgums to eat the ghosts\n- Don't get caught by the ghosts\nCONTROLS:"
  "\n- UP/DOWN/LEFT/RIGHT: Move";
  this->getCoreModule()->setGameData(data);
  this->setDirection(arcade::KeyboardInput::RIGHT);
}

std::string arcade::Pacman::getName() { return "pacman"; }

void arcade::Pacman::updateGame()
{
  arcade::GameData data = this->getCoreModule()->getGameData();
  std::vector<arcade::timer> timers =
      this->getCoreModule()->getTimers();
  int speedVector = timers[0].duration.count() / 10;
  if (speedVector > 0)
    this->getCoreModule()->resetTimers(0);
  for (int i = 0; i < speedVector; i += 1) {
    data = this->movePacman(data);
  }
  if (timers[1].duration.count() > 10000){
    data.entities[0][178].sprite = EMPTY; // true
    for (int i = 0; i < speedVector; i += 1) {
      data = this->moveGhosts(data);
    }
  }
  this->getCoreModule()->setGameData(data);
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


void deleteElementInLayer(std::vector<arcade::entity> &layer, int x, int y)
{
  for (int i = 0; i < layer.size(); i += 1) {
    if (layer[i].position.first == x && layer[i].position.second == y) {
      layer.erase(layer.begin() + i);
      return;
    }
  }
}

arcade::GameData arcade::Pacman::movePacman(arcade::GameData &data)
{
  std::vector<arcade::entity> pacman = data.entities[PACMAN_LAYER];
  std::pair<int, int> pacmanPos = pacman.front().position;


  if (this->_direction == arcade::KeyboardInput::UP && pacmanPos.first % 30 == 0) {
    this->_oldDirection = this->_direction;
  } else if (this->_direction == arcade::KeyboardInput::DOWN &&
             pacmanPos.first % 30 == 0) {
    this->_oldDirection = this->_direction;
  } else if (this->_direction == arcade::KeyboardInput::LEFT &&
             pacmanPos.second % 30 == 0) {
    this->_oldDirection = this->_direction;
  } else if (this->_direction == arcade::KeyboardInput::RIGHT &&
             pacmanPos.second % 30 == 0) {
    this->_oldDirection = this->_direction;
  }
  switch (this->_oldDirection) {
  case arcade::KeyboardInput::UP:
    pacman.front().position.second -= this->_gameSpeed;
    break;
  case arcade::KeyboardInput::DOWN:
    pacman.front().position.second += this->_gameSpeed;
    break;
  case arcade::KeyboardInput::LEFT:
    pacman.front().position.first -= this->_gameSpeed;
    break;
  case arcade::KeyboardInput::RIGHT:
    pacman.front().position.first += this->_gameSpeed;
    break;
  }

  // Check if the pacman is eating a coin
  if (getLayerCell(COIN_LAYER, pacman.front().position.first, pacman.front().position.second) == COIN){
    data.score += 10;
    deleteElementInLayer(data.entities[COIN_LAYER], pacman.front().position.first, pacman.front().position.second);
  }

  // Check if the pacman is eating a super pacgum
  if (getLayerCell(COIN_LAYER, pacman.front().position.first, pacman.front().position.second) == SUPERPACGUM) {
    for (int i = 0; i < data.entities[GHOSTS_LAYER].size(); i += 1) {
      data.entities[GHOSTS_LAYER][i].sprite = SCAREDGHOSTS;
      this->_ghostspeed = this->_ghostspeed;
      this->_ghostState = FEAR;
    }
    // reset fear timer
    this->getCoreModule()->resetTimers(2);
    deleteElementInLayer(data.entities[COIN_LAYER], pacman.front().position.first, pacman.front().position.second);
    data.score += 50;
  }

  // Check if the pacman is hitting a wall
  if (this->getLayerCell(
          MAP_LAYER, pacman.front().position.first, pacman.front().position.second) == WALL ||
      this->getLayerCell(
          MAP_LAYER, pacman.front().position.first + (30 - this->_gameSpeed), pacman.front().position.second) == WALL ||
      this->getLayerCell(
          MAP_LAYER, pacman.front().position.first - (30 - this->_gameSpeed), pacman.front().position.second) == WALL ||
      this->getLayerCell(
          MAP_LAYER, pacman.front().position.first, pacman.front().position.second + (30 - this->_gameSpeed)) == WALL ||
      this->getLayerCell(
          MAP_LAYER, pacman.front().position.first, pacman.front().position.second - (30 - this->_gameSpeed)) == WALL) {
    return data;
  }

  // Check if the pacman is attempting to eat a ghost when the ghost is not scared
  if (this->getLayerCell(
          GHOSTS_LAYER, pacman.front().position.first, pacman.front().position.second) == GHOSTS ||
      this->getLayerCell(
          GHOSTS_LAYER, pacman.front().position.first + (30 - this->_gameSpeed), pacman.front().position.second) == GHOSTS ||
      this->getLayerCell(
          GHOSTS_LAYER, pacman.front().position.first - (30 - this->_gameSpeed), pacman.front().position.second) == GHOSTS ||
      this->getLayerCell(
          GHOSTS_LAYER, pacman.front().position.first, pacman.front().position.second + (30 - this->_gameSpeed)) == GHOSTS ||
      this->getLayerCell(
          GHOSTS_LAYER, pacman.front().position.first, pacman.front().position.second - (30 - this->_gameSpeed)) == GHOSTS) {
    this->_gameStatus = arcade::IGameModule::GAMEOVER;
    this->getCoreModule()->setCoreStatus(arcade::ICoreModule::SELECTION);
  // Check if the pacman is attempting to eat a ghost when the ghost is scared
  } else if (this->getLayerCell(
          GHOSTS_LAYER, pacman.front().position.first, pacman.front().position.second) == SCAREDGHOSTS ||
      this->getLayerCell(
          GHOSTS_LAYER, pacman.front().position.first + (30 - this->_gameSpeed), pacman.front().position.second) == SCAREDGHOSTS ||
      this->getLayerCell(
          GHOSTS_LAYER, pacman.front().position.first - (30 - this->_gameSpeed), pacman.front().position.second) == SCAREDGHOSTS ||
      this->getLayerCell(
          GHOSTS_LAYER, pacman.front().position.first, pacman.front().position.second + (30 - this->_gameSpeed)) == SCAREDGHOSTS ||
      this->getLayerCell(
          GHOSTS_LAYER, pacman.front().position.first, pacman.front().position.second - (30 - this->_gameSpeed)) == SCAREDGHOSTS) {
    for (int i = 0; i < data.entities[GHOSTS_LAYER].size(); i += 1) {
      if (data.entities[GHOSTS_LAYER][i].position == pacman.front().position) {
        deleteElementInLayer(data.entities[GHOSTS_LAYER], pacman.front().position.first, pacman.front().position.second);
        data.entities[GHOSTS_LAYER].push_back((arcade::entity){.sprite = GHOSTS_DEATH, .position = pacman.front().position});
        this->_ghostState = DEATH;
        data.score += 100;
      }
    }

    return data;
  }

  // update body position
  if (pacman.front().position.first + 30 < pacman.front().position.first &&
      pacman.front().position.second == pacman.front().position.second)
    pacman.front().position = std::make_pair(pacman.front().position.first + this->_gameSpeed,
                                        pacman.front().position.second);
  else if (pacman.front().position.first - 30 > pacman.front().position.first &&
            pacman.front().position.second == pacman.front().position.second)
    pacman.front().position = std::make_pair(pacman.front().position.first - this->_gameSpeed,
                                        pacman.front().position.second);
  else if (pacman.front().position.second + 30 < pacman.front().position.second &&
            pacman.front().position.first == pacman.front().position.first)
    pacman.front().position = std::make_pair(
        pacman.front().position.first, pacman.front().position.second + this->_gameSpeed);
  else if (pacman.front().position.second - 30 > pacman.front().position.second &&
            pacman.front().position.first == pacman.front().position.first)
    pacman.front().position = std::make_pair(
        pacman.front().position.first, pacman.front().position.second - this->_gameSpeed);

  data.entities[PACMAN_LAYER] = pacman;
  return data;
}

bool arcade::Pacman::isGhostsHittingWall(arcade::entity ghosts)
{
  if (this->getLayerCell(
          MAP_LAYER, ghosts.position.first, ghosts.position.second) == WALL ||
      this->getLayerCell(
          MAP_LAYER, ghosts.position.first + (30 - this->_ghostspeed), ghosts.position.second) == WALL ||
      this->getLayerCell(
          MAP_LAYER, ghosts.position.first - (30 - this->_ghostspeed), ghosts.position.second) == WALL ||
      this->getLayerCell(
          MAP_LAYER, ghosts.position.first, ghosts.position.second + (30 - this->_ghostspeed)) == WALL ||
      this->getLayerCell(
          MAP_LAYER, ghosts.position.first, ghosts.position.second - (30 - this->_ghostspeed)) == WALL) {
    return true;
  }
  return false;
}

arcade::GameData arcade::Pacman::moveGhosts(arcade::GameData &data)
{
  std::vector<arcade::entity> ghosts = data.entities[GHOSTS_LAYER];

  for (int i = 0; i < ghosts.size(); i += 1) {
    std::pair<int, int> ghostPos = ghosts[i].position;
    std::pair<int, int> pacmanPos = data.entities[PACMAN_LAYER].front().position;
    if (this->_ghostState == HUNTING) {
      if (ghostPos.first < pacmanPos.first && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first + this->_ghostspeed, ghosts[i].position.second)}) == false) && (ghostPos.second % 30 == 0)) {
        ghosts[i].position.first += this->_ghostspeed;
      } else if (ghostPos.first > pacmanPos.first && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first - this->_ghostspeed, ghosts[i].position.second)}) == false) && (ghostPos.second % 30 == 0)) {
        ghosts[i].position.first -= this->_ghostspeed;
      } else if (ghostPos.second < pacmanPos.second && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second + this->_ghostspeed)}) == false) && (ghostPos.first % 30 == 0)) {
        ghosts[i].position.second += this->_ghostspeed;
      } else if (ghostPos.second > pacmanPos.second && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second - this->_ghostspeed)}) == false) && (ghostPos.first % 30 == 0)) {
        ghosts[i].position.second -= this->_ghostspeed;
      } else {
        if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first + this->_ghostspeed, ghosts[i].position.second)}) == false  && (ghostPos.second % 30 == 0)) {
          ghosts[i].position.first += this->_ghostspeed;
        } else if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first - this->_ghostspeed, ghosts[i].position.second)}) == false  && (ghostPos.second % 30 == 0)) {
          ghosts[i].position.first -= this->_ghostspeed;
        } else if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second + this->_ghostspeed)}) == false  && (ghostPos.first % 30 == 0)) {
          ghosts[i].position.second += this->_ghostspeed;
        } else if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second - this->_ghostspeed)}) == false  && (ghostPos.first % 30 == 0)) {
          ghosts[i].position.second -= this->_ghostspeed;
        }
      }
    } else if (this->_ghostState == FEAR) {
      if (ghostPos.first < this->_ghost[i].destination.first && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first + this->_ghostspeed, ghosts[i].position.second)}) == false) && (ghostPos.second % 30 == 0)) {
        ghosts[i].position.first += this->_ghostspeed;
      } else if (ghostPos.first > this->_ghost[i].destination.first && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first - this->_ghostspeed, ghosts[i].position.second)}) == false) && (ghostPos.second % 30 == 0)) {
        ghosts[i].position.first -= this->_ghostspeed;
      } else if (ghostPos.second < this->_ghost[i].destination.second && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second + this->_ghostspeed)}) == false) && (ghostPos.first % 30 == 0)) {
        ghosts[i].position.second += this->_ghostspeed;
      } else if (ghostPos.second > this->_ghost[i].destination.second && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second - this->_ghostspeed)}) == false) && (ghostPos.first % 30 == 0)) {
        ghosts[i].position.second -= this->_ghostspeed;
      } else {
        if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first + this->_ghostspeed, ghosts[i].position.second)}) == false  && (ghostPos.second % 30 == 0)) {
          ghosts[i].position.first += this->_ghostspeed;
        } else if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first - this->_ghostspeed, ghosts[i].position.second)}) == false  && (ghostPos.second % 30 == 0)) {
          ghosts[i].position.first -= this->_ghostspeed;
        } else if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second + this->_ghostspeed)}) == false  && (ghostPos.first % 30 == 0)) {
          ghosts[i].position.second += this->_ghostspeed;
        } else if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second - this->_ghostspeed)}) == false  && (ghostPos.first % 30 == 0)) {
          ghosts[i].position.second -= this->_ghostspeed;
        }
      }
    } else if (this->_ghostState == DEATH) {
      if (ghostPos.first < GHOST_START_1.first && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first + this->_ghostspeed, ghosts[i].position.second)}) == false) && (ghostPos.second % 30 == 0)) {
        ghosts[i].position.first += this->_ghostspeed;
      } else if (ghostPos.first > GHOST_START_1.first && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first - this->_ghostspeed, ghosts[i].position.second)}) == false) && (ghostPos.second % 30 == 0)) {
        ghosts[i].position.first -= this->_ghostspeed;
      } else if (ghostPos.second < GHOST_START_1.second && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second + this->_ghostspeed)}) == false) && (ghostPos.first % 30 == 0)) {
        ghosts[i].position.second += this->_ghostspeed;
      } else if (ghostPos.second > GHOST_START_1.second && (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second - this->_ghostspeed)}) == false) && (ghostPos.first % 30 == 0)) {
        ghosts[i].position.second -= this->_ghostspeed;
      } else {
        if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first + this->_ghostspeed, ghosts[i].position.second)}) == false  && (ghostPos.second % 30 == 0)) {
          ghosts[i].position.first += this->_ghostspeed;
        } else if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first - this->_ghostspeed, ghosts[i].position.second)}) == false && (ghostPos.second % 30 == 0)) {
          ghosts[i].position.first -= this->_ghostspeed;
        } else if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second + this->_ghostspeed)}) == false && (ghostPos.first % 30 == 0)) {
          ghosts[i].position.second += this->_ghostspeed;
        } else if (isGhostsHittingWall((entity){.position= std::make_pair(ghosts[i].position.first, ghosts[i].position.second - this->_ghostspeed)}) == false && (ghostPos.first % 30 == 0)) {
          ghosts[i].position.second -= this->_ghostspeed;
        }
      }
    }
  }


  data.entities[GHOSTS_LAYER] = ghosts;
  return data;
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
