/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SDL2
*/

#ifndef SDL2_HPP_
#define SDL2_HPP_

#include "IDisplayModule.hpp"

namespace arcade {
class SDL2 : virtual public arcade::IDisplayModule {
public:
  SDL2();
  ~SDL2();

protected:
private:
};
}; // namespace arcade

#endif /* !SDL2_HPP_ */
