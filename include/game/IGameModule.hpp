/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include "CoreModule.hpp"
#include "Arcade.hpp"

namespace arcade {
class CoreModule;
class IGameModule {
public:
  enum GameStatus { RUNNING, PAUSED, GAMEOVER, WIN };
  IGameModule(){};
  virtual ~IGameModule(){};

  virtual void setGameStatus(GameStatus status) = 0;
  virtual GameStatus getDisplayStatus() const = 0;

  virtual void sendInput(arcade::KeyboardInput input) = 0;
  virtual arcade::GameData sendGameData() = 0;

  virtual void setCoreModule(arcade::CoreModule *coreModule) = 0;
  virtual arcade::CoreModule *getCoreModule() const = 0;

protected:
  GameStatus _gameStatus;
  arcade::CoreModule *_coreModule;
};
}; // namespace arcade

#endif /* !IGAMEMODULE_HPP_ */
