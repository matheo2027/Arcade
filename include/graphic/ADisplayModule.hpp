/*
** EPITECH PROJECT, 2024
** bsArcade
** File description:
** ADisplayModule
*/

#ifndef ADISPLAYMODULE_HPP_
#define ADISPLAYMODULE_HPP_

#include "IDisplayModule.hpp"
namespace arcade {
class ADisplayModule : virtual public arcade::IDisplayModule {
public:
  ADisplayModule();
  ~ADisplayModule();

  virtual void display() = 0;
  virtual void displayMenu() = 0;
  virtual void displayGame() = 0;
  void setDisplayStatus(DisplayStatus status);
  DisplayStatus getDisplayStatus() const;

  void sendGameData(arcade::GameData data);
  void sendMenuData(arcade::MenuData data);

  void setCoreModule(arcade::CoreModule *coreModule);
  arcade::CoreModule *getCoreModule() const;
};
}; // namespace arcade

#endif /* !ADISPLAYMODULE_HPP_ */
