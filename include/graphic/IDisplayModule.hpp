/*
** EPITECH PROJECT, 2024
** bsArcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

// #include "CoreModule.hpp"
#include "IModule.hpp"


namespace arcade {
class CoreModule;
class IDisplayModule : virtual public arcade::IModule {
public:
  enum DisplayStatus { RUNNING, PAUSED, SELECTION, GAMEOVER, WIN };
  IDisplayModule(){};
  virtual ~IDisplayModule(){};
  virtual void init() = 0;
  virtual void stop() = 0;

  virtual void display() = 0;
  virtual void displayMenu() = 0;
  virtual void displayGame() = 0;

  virtual void setDisplayStatus(DisplayStatus status) = 0;
  virtual DisplayStatus getDisplayStatus() const = 0;

  virtual arcade::IModule::LibName getName() const = 0;
  virtual arcade::IModule::ModuleType getType() const = 0;

  void sendGameData(arcade::IModule::GameData data);
  void sendMenuData(arcade::IModule::MenuData data);

//  virtual void setCoreModule(arcade::CoreModule *coreModule) = 0;
//  virtual arcade::CoreModule *getCoreModule() const = 0;

protected:
  DisplayStatus _displayStatus;
  arcade::CoreModule *_coreModule;
};
}; // namespace arcade

#endif /* !IDISPLAYMODULE_HPP_ */
