/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include "CoreModule.hpp"
#include "IModule.hpp"

namespace arcade {
class CoreModule;
class IGameModule : virtual public arcade::IModule {
public:
  enum GameStatus { RUNNING, PAUSED, GAMEOVER, WIN };
  IGameModule(){};
  virtual ~IGameModule(){};
  virtual void init() = 0;
  virtual void stop() = 0;

  virtual void setGameStatus(GameStatus status) = 0;
  virtual GameStatus getDisplayStatus() const = 0;

  virtual arcade::IModule::LibName getName() const = 0;
  virtual arcade::IModule::ModuleType getType() const = 0;

  virtual void sendInput(arcade::IModule::KeyboardInput input) = 0;
  virtual arcade::IModule::GameData sendGameData() = 0;

  virtual void setCoreModule(arcade::CoreModule *coreModule) = 0;
  virtual arcade::CoreModule *getCoreModule() const = 0;

protected:
  GameStatus _gameStatus;
  arcade::CoreModule *_coreModule;
};
}; // namespace arcade

#endif /* !IGAMEMODULE_HPP_ */
