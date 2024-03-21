/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#ifndef COREMODULE_HPP_
#define COREMODULE_HPP_

#include "IModule.hpp"
namespace arcade {
class CoreModule : virtual public arcade::IModule {
public:
  CoreModule();
  ~CoreModule();
  enum CoreStatus { RUNNING, SELECTION };
  void setCoreStatus(CoreStatus status);
  CoreStatus getCoreStatus() const;
protected:
  CoreStatus _coreStatus;
};
}; // namespace arcade

#endif /* !COREMODULE_HPP_ */
