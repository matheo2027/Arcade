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
class SFML : virtual public arcade::ADisplayModule {
public:
    SFML();
    ~SFML();

    arcade::IModule::KeyboardInput getInput();
    void init();
    void stop();
    void display(const arcade::IModule::GameData &data);


protected:
private:
    sf::RenderWindow _window;
    sf::Texture _texture;
    sf::Font _font;
};
};


#endif /* !SFML_HPP_ */
