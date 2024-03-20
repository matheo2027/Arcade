/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include <string>

class IModule {
public:
  IModule();
  ~IModule();
  virtual const std::string &getName() const = 0;
  virtual const std::string &getType() const = 0;

protected:
private:
};

#endif /* !IMODULE_HPP_ */
