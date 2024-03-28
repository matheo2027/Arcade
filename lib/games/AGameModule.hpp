/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGameModule
*/

#ifndef AGAMEMODULE_HPP_
#define AGAMEMODULE_HPP_

#include <arcade/IGameModule.hpp>
#include <chrono>

namespace arcade {
class AGameModule : virtual public arcade::IGameModule {
public:
  AGameModule();
  ~AGameModule();

  virtual void init() = 0;
  virtual void updateGame() = 0;

  void setGameStatus(GameStatus status);
  GameStatus getDisplayStatus() const;

  void sendInput(arcade::KeyboardInput input);
  arcade::GameData sendGameData();

  void setCoreModule(arcade::CoreModule *coreModule);
  arcade::CoreModule *getCoreModule() const;

  void updateTimer();
  void resetTimer();
  timer getTimer() const;

  void setDirection(arcade::KeyboardInput direction);
  arcade::KeyboardInput getDirection() const;

  virtual void handdleKeyEvents(arcade::KeyboardInput key) = 0;
};
}; // namespace arcade

#endif /* !IGAMEMODULE_HPP_ */
