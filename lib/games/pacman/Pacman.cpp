/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Pacman
*/

#include "Pacman.hpp"

arcade::Pacman::Pacman() : arcade::IModule(), arcade::AGameModule() {}

arcade::Pacman::~Pacman() {}

/**
 * @brief initialize the game pacman
 * 
 */
void init() { return; }

/**
 * @brief stop the game pacman
 * 
 */
void stop() { return; }

/**
 * @brief return the name of the game pacman
 * 
 * @return const arcade::IModule::LibName
 */
const arcade::IModule::LibName arcade::Pacman::getName() const
{
  return arcade::IModule::LibName::PACMAN;
}

extern "C" arcade::Pacman *entryPoint() { return new arcade::Pacman(); }