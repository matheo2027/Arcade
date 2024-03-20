/*
** EPITECH PROJECT, 2024
** bsArcade
** File description:
** IDisplayModule
*/

#ifndef IDISPLAYMODULE_HPP_
#define IDISPLAYMODULE_HPP_

#include <string>

class IDisplayModule {
public:
  virtual ~IDisplayModule() = default;
  virtual void init() = 0;
  virtual void stop() = 0;
  virtual const std ::string &getName() const = 0;
};

#endif /* !IDISPLAYMODULE_HPP_ */
