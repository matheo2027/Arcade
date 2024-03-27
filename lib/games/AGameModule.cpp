/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGameModule
*/

#include "AGameModule.hpp"

/**
 * @brief Construct a new arcade::A Game Module::A Game Module object
 *
 */
arcade::AGameModule::AGameModule()
{
  this->_gameStatus = GameStatus::RUNNING;
}

/**
 * @brief Destroy the arcade::A Game Module::A Game Module object
 *
 */
arcade::AGameModule::~AGameModule() {}

void arcade::AGameModule::setGameStatus(arcade::AGameModule::GameStatus status)
{
  this->_gameStatus = status;
}

/**
 * @brief get the status of the game
 *
 * @return arcade::AGameModule::GameStatus
 */
arcade::AGameModule::GameStatus arcade::AGameModule::getDisplayStatus() const
{
  return this->_gameStatus;
}

/**
 * @brief receive input from the graphic module
 *
 * @param input KeyboardInput
 */
void arcade::AGameModule::sendInput(arcade::KeyboardInput input)
{
  return;
}


/**
 * @brief send the game data to the graphic module
 *
 * @return arcade::GameData
 */
arcade::GameData arcade::AGameModule::sendGameData()
{
  return arcade::GameData();
}

/**
 * @brief set the core module to the game module
 *
 * @param coreModule
 */
void arcade::AGameModule::setCoreModule(arcade::CoreModule *coreModule)
{
  std::cout << "setCoreModule" << std::endl;
  this->_coreModule = coreModule;
}

/**
 * @brief get the core module
 *
 * @return arcade::CoreModule *
 */
arcade::CoreModule *arcade::AGameModule::getCoreModule() const
{
  return this->_coreModule;
}
