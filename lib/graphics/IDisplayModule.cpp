/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IDisplayModule
*/

#include "IDisplayModule.hpp"

arcade::IDisplayModule::IDisplayModule() {}

arcade::IDisplayModule::~IDisplayModule() {}

const arcade::IModule::ModuleType arcade::IDisplayModule::getType() const
{
  return arcade::IModule::ModuleType::GRAPHIC;
}

arcade::IModule::KeyboardInput arcade::IDisplayModule::getInput()
{
    return arcade::IModule::KeyboardInput::UP;
}

void arcade::IDisplayModule::sendGameData(arcade::IModule::GameData data)
{
    return;
}