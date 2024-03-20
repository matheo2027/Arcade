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