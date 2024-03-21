/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2
*/

#ifndef SDL2_HPP_
#define SDL2_HPP_

#include "ADisplayModule.hpp"
#include <SDL2/SDL.h>

namespace arcade {
class SDL2 : virtual public arcade::ADisplayModule {
public:
  SDL2();
  ~SDL2();
  void init();
  void stop();

protected:
private:
};
}; // namespace arcade

#endif /* !SDL2_HPP_ */
