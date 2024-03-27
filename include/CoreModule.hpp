/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#ifndef COREMODULE_HPP_
#define COREMODULE_HPP_

#include "Arcade.hpp"
#include "DLLoader.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include <dirent.h>

namespace arcade {
class IDisplayModule;
class IGameModule;
class CoreModule {
public:
  CoreModule();
  ~CoreModule();

  enum CoreStatus { RUNNING, SELECTION, EXIT };

  void setCoreStatus(CoreStatus status);
  CoreStatus getCoreStatus() const;

  arcade::IDisplayModule *getGraphicModule();
  arcade::IGameModule *getGameModule();

  void setGraphicModule(std::unique_ptr<arcade::IDisplayModule> module);
  void setGameModule(std::unique_ptr<arcade::IGameModule> module);

  void getLib(std::string pathLib);
  void loadLib(std::string pathLib);
  void addLibList(std::string pathLib);

  void handleKeyEvent(arcade::KeyboardInput key);
  void handleKeySelection(arcade::KeyboardInput key);
  void handleKeyRunning(arcade::KeyboardInput key);

  arcade::MenuData getMenuData() const;

  void setGameData(arcade::GameData gameData);
  arcade::GameData getGameData() const;

protected:
  CoreStatus _coreStatus;
  arcade::IDisplayModule *_graphicModule;
  arcade::IGameModule *_gameModule;
  arcade::MenuData _menuData;
  arcade::GameData _gameData;
};
}; // namespace arcade

#endif /* !COREMODULE_HPP_ */
