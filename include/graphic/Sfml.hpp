/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "ADisplayModule.hpp"
#include <SFML/Graphics.hpp>

namespace arcade {
class Sfml : virtual public arcade::ADisplayModule {
public:
  Sfml();
  ~Sfml();

  arcade::KeyboardInput getInput();
  void display();
  void displayMenu();
  void displayGame();

protected:
  sf::RenderWindow _window;
  sf::Texture _texture;
  sf::Font _font;
};
}; // namespace arcade

#endif /* !SFML_HPP_ */
