/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ICoreModule
*/

#ifndef ICOREMODULE_HPP_
#define ICOREMODULE_HPP_

#include <Arcade.hpp>
#include <arcade/IDisplayModule.hpp>
#include <arcade/IGameModule.hpp>
#include <dirent.h>
#include <iostream>

namespace arcade {
class IDisplayModule;
class IGameModule;
class ICoreModule {
public:
  ICoreModule(){};
  virtual ~ICoreModule(){};

  enum CoreStatus { RUNNING, SELECTION, EXIT };
  virtual void setCoreStatus(CoreStatus status) = 0;
  virtual CoreStatus getCoreStatus() const = 0;

  virtual arcade::IDisplayModule *getGraphicModule() = 0;
  virtual arcade::IGameModule *getGameModule() = 0;

  virtual void
  setGraphicModule(std::unique_ptr<arcade::IDisplayModule> module) = 0;
  virtual void setGameModule(std::unique_ptr<arcade::IGameModule> module) = 0;

  virtual void getLib(std::string pathLib) = 0;
  virtual void loadLib(std::string pathLib) = 0;
  virtual void addLibList(std::string pathLib) = 0;
  virtual void generateScore() = 0;

  virtual void handleKeyEvent(arcade::KeyboardInput key) = 0;
  virtual void handleKeySelection(arcade::KeyboardInput key) = 0;
  virtual void handleKeyRunning(arcade::KeyboardInput key) = 0;

  // MENU SELECTION
  enum MenuSelection { USERNAME, GAME, GRAPHIC };
  struct MenuData {
    std::string _username;
    int indexGame;
    std::vector<std::string> _gameLibList;
    int indexGraphic;
    std::vector<std::string> _graphicLibList;
    std::string _description;
    MenuSelection _type;
  };

  virtual MenuData getMenuData() const = 0;

  virtual void setGameData(arcade::GameData gameData) = 0;
  virtual arcade::GameData getGameData() const = 0;

  virtual int coreLoop() = 0;
  virtual void runningLoop() = 0;
  virtual void updateRunning() = 0;
  virtual void selectionLoop() = 0;
  virtual void updateSelection() = 0;

  virtual void updateTimers() = 0;
  virtual void resetTimers(int index) = 0;
  virtual std::vector<timer> getTimers() const = 0;
  virtual void setTimers(std::vector<arcade::timer> timers) = 0;


protected:
  CoreStatus _coreStatus;
  std::vector<timer> _timers;
  arcade::IDisplayModule *_graphicModule;
  arcade::IGameModule *_gameModule;
  arcade::ICoreModule::MenuData _menuData;
  arcade::GameData _gameData;
};
}; // namespace arcade

#endif /* !ICOREMODULE_HPP_ */
