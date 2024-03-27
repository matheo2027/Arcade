/*
** EPITECH PROJECT, 2024
** bsArcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include "Arcade.hpp"
#include "CoreModule.hpp"
namespace arcade {
class CoreModule;
class IDisplayModule {
public:
  enum DisplayStatus { RUNNING, PAUSED, SELECTION, GAMEOVER, WIN };

  IDisplayModule(){};
  virtual ~IDisplayModule(){};

  virtual void display() = 0;
  virtual void displayMenu() = 0;
  virtual void displayGame() = 0;

  virtual void setDisplayStatus(DisplayStatus status) = 0;
  virtual DisplayStatus getDisplayStatus() const = 0;

  void sendGameData(arcade::GameData data);
  void sendMenuData(arcade::MenuData data);

  virtual void setCoreModule(arcade::CoreModule *coreModule) = 0;
  virtual arcade::CoreModule *getCoreModule() const = 0;

protected:
  DisplayStatus _displayStatus;
  arcade::CoreModule *_coreModule;
};
}; // namespace arcade

#endif /* !IDISPLAYMODULE_HPP_ */
