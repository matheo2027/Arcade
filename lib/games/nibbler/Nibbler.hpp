/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
#define NIBBLER_HPP_

#include "../AGameModule.hpp"

namespace arcade {
    class Nibbler : virtual public arcade::AGameModule {
    public:
    #define HEAD 'N'
    #define BODY '-'
    #define FOOD 'F'
    #define WALL '#'
    #define EMPTY ' '
    #define NIBBLER_SPEED 1
    #define MAP_LAYER 0
    #define FOOD_LAYER 1
    #define NIBBLER_LAYER 2
      Nibbler();
      ~Nibbler();
      std::string getName();
      void init();
      void updateGame();
      arcade::GameData moveNibbler();
      void handdleKeyEvents(arcade::KeyboardInput key);
    };
}; // namespace arcade

#endif /* !NIBBLER_HPP_ */
