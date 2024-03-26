/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#ifndef COREMODULE_HPP_
#define COREMODULE_HPP_

#include "DLLoader.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "IModule.hpp"
#include <dirent.h>

namespace arcade {
class IDisplayModule;
class IGameModule;
class CoreModule : virtual public arcade::IModule {
public:
  CoreModule();
  ~CoreModule();
  void init();
  void stop();
  LibName getName() const;
  ModuleType getType() const;
  enum CoreStatus { RUNNING, SELECTION, EXIT };

  void setCoreStatus(CoreStatus status);
  CoreStatus getCoreStatus() const;

  arcade::IDisplayModule *getGraphicModule();
  arcade::IGameModule *getGameModule();

  void setModule(arcade::IModule *module, arcade::IModule::ModuleType type);

  void getLib(std::string pathLib);
  void loadLib(std::string pathLib);
  void addLibList(std::string pathLib);

  void handleKeyEvent(arcade::IModule::KeyboardInput key);
  void handleKeySelection(arcade::IModule::KeyboardInput key);
  void handleKeyRunning(arcade::IModule::KeyboardInput key);

  arcade::IModule::MenuData getMenuData() const;

  void setGameData(arcade::IModule::GameData gameData);
  arcade::IModule::GameData getGameData() const;

protected:
  CoreStatus _coreStatus;
  arcade::IDisplayModule *_graphicModule;
  arcade::IGameModule *_gameModule;
  arcade::IModule::MenuData _menuData;
  arcade::IModule::GameData _gameData;
};
}; // namespace arcade

#endif /* !COREMODULE_HPP_ */
