/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#include "CoreModule.hpp"

arcade::CoreModule::CoreModule() : arcade::IModule()
{
    this->_coreStatus = CoreStatus::SELECTION;
}

arcade::CoreModule::~CoreModule()
{
}

void arcade::CoreModule::setCoreStatus(CoreStatus status)
{
    this->_coreStatus = status;
}

arcade::CoreModule::CoreStatus arcade::CoreModule::getCoreStatus() const
{
    return this->_coreStatus;
}