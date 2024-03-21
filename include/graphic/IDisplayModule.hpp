/*
** EPITECH PROJECT, 2024
** bsArcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include "IModule.hpp"

namespace arcade {
class IDisplayModule : virtual public arcade::IModule {
public:
  enum DisplayStatus { RUNNING, PAUSED, GAMEOVER, WIN };
  IDisplayModule();
  virtual ~IDisplayModule() = 0;
  virtual void init() = 0;
  virtual void stop() = 0;
  virtual const arcade::IModule::LibName getName() const = 0;
  const arcade::IModule::ModuleType getType() const;
  arcade::IModule::KeyboardInput getInput();
  void sendGameData(arcade::IModule::GameData data);
};
}; // namespace arcade

#endif /* !IDISPLAYMODULE_HPP_ */
