/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGameModule
*/

#include "IGameModule.hpp"

arcade::IGameModule::IGameModule() : arcade::IModule() {}

arcade::IGameModule::~IGameModule() {}

const arcade::IModule::ModuleType arcade::IGameModule::getType() const
{
  return arcade::IModule::ModuleType::GAME;
}

void arcade::IGameModule::sendInput(arcade::IModule::KeyboardInput input)
{
    return;
}

arcade::IModule::GameData arcade::IGameModule::sendGameData()
{
    return arcade::IModule::GameData();
}