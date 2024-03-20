/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include <string>

namespace arcade {
class IModule {
public:
  IModule();
  ~IModule();
  virtual void init() = 0;
  virtual void stop() = 0;
  enum ModuleType { GRAPHIC, GAME };
  enum LibName {
    // GAME
    PACMAN,
    NIBBLER,
    CENTIPEDE,
    SOLARFOX,
    // GRAPHIC
    SFML,
    NCURSES,
    SDL,
    OPENGL,
    UNKNOWN
  };
  virtual const LibName getName() const = 0;
  virtual const ModuleType getType() const = 0;
};
}; // namespace arcade

#endif /* !IMODULE_HPP_ */
