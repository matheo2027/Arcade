/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** SFML
*/

#include "Sfml.hpp"

arcade::SFML::SFML() : IModule(), ADisplayModule()
{
}

arcade::SFML::~SFML()
{
}


void arcade::SFML::init()
{
    _window.create(sf::VideoMode(1920, 1080), "Arcade");
    _window.setFramerateLimit(60);
}

void arcade::SFML::stop()
{
    _window.close();
}

void arcade::SFML::display(const arcade::IModule::GameData &data)
{
    _window.clear();
    for (int y = 0; y < data.display_info.size(); y++) {
        for (int x = 0; x < data.display_info[y].size(); x++) {
            sf::RectangleShape rectangle(sf::Vector2f(20, 20));
            rectangle.setPosition(x * 20, y * 20);
            rectangle.setFillColor(sf::Color::White);
            _window.draw(rectangle);
        }
    }
    _window.display();
}

arcade::IModule::KeyboardInput arcade::SFML::getInput()
{
    sf::Event event;

    while (this->_window.pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
            // case sf::Event::Closed:

            case sf::Keyboard::Up:
                return arcade::IModule::KeyboardInput::UP;
            case sf::Keyboard::Down:
                return arcade::IModule::KeyboardInput::DOWN;
            case sf::Keyboard::Left:
                return arcade::IModule::KeyboardInput::LEFT;
            case sf::Keyboard::Right:
                return arcade::IModule::KeyboardInput::RIGHT;
            case sf::Keyboard::Space:
                return arcade::IModule::KeyboardInput::SPACE;
            case sf::Keyboard::Escape:
                return arcade::IModule::KeyboardInput::ESCAPE;
            default:
                break;
            }
            break;

        default:
            break;
        }
    }
    return arcade::IModule::KeyboardInput::NONE;
}