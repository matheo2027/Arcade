/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include "IModule.hpp"

namespace arcade {
class IGameModule : virtual public arcade::IModule {
public:
  IGameModule();
  virtual ~IGameModule() = 0;
  virtual void init() = 0;
  virtual void stop() = 0;
  virtual const arcade::IModule::LibName getName() const = 0;
  const arcade::IModule::ModuleType getType() const;
};
}; // namespace arcade

#endif /* !IGAMEMODULE_HPP_ */
