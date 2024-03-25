/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Sfml
*/

#include "Sfml.hpp"
#include "Error.hpp"

/**
 * @brief Construct a new arcade::Sfml::Sfml object
 *
 */
arcade::Sfml::Sfml() : IModule(), ADisplayModule() {}

/**
 * @brief Destroy the arcade::Sfml::Sfml object
 *
 */
arcade::Sfml::~Sfml() {}

/**
 * @brief init the window
 *
 */
void arcade::Sfml::init()
{
  sf::RenderWindow *window =
      new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade");
  window->setFramerateLimit(60);
  window->clear(sf::Color::Black);
  window->display();
  this->_window = window;
}

/**
 * @brief stop the window
 *
 */
void arcade::Sfml::stop()
{
  sf::RenderWindow *window = static_cast<sf::RenderWindow *>(this->_window);
  if (window == nullptr) {
    try {
      throw NoWindowException("No window to stop");
    } catch (NoWindowException &e) {
      std::cerr << e.what() << std::endl;
    }
  }
  window->close();
  this->_window = nullptr;
}

/**
 * @brief display the game info in the window
 *
 */
void arcade::Sfml::display()
{
  sf::RenderWindow *window = static_cast<sf::RenderWindow *>(this->_window);
  if (window == nullptr) {
    try {
      throw NoWindowException("No window to stop");
    } catch (NoWindowException &e) {
      std::cerr << e.what() << std::endl;
    }
  }
  window->clear();
  for (int y = 0; y < this->_gameData.display_info.size(); y++) {
    for (int x = 0; x < this->_gameData.display_info[y].size(); x++) {
      sf::RectangleShape rectangle(sf::Vector2f(20, 20));
      rectangle.setPosition(x * 20, y * 20);
      rectangle.setFillColor(sf::Color::White);
      window->draw(rectangle);
    }
  }
  window->display();
  this->_window = window;
}

/**
 * @brief return the name of the library
 *
 * @return arcade::IModule::LibName
 */
arcade::IModule::LibName arcade::Sfml::getName() const
{
  return arcade::IModule::LibName::SFML;
}

/**
 * @brief get the keyboard input
 *
 * @return arcade::IModule::KeyboardInput
 */
arcade::IModule::KeyboardInput arcade::Sfml::getInput()
{
  sf::RenderWindow *window = static_cast<sf::RenderWindow *>(this->_window);
  if (window == nullptr) {
    try {
      throw NoWindowException("No window to stop");
    } catch (NoWindowException &e) {
      std::cerr << e.what() << std::endl;
    }
  }
  sf::Event event;

  while (window->pollEvent(event)) {
    switch (event.type) {
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

/**
 * @brief entry point for the library
 *
 * @return arcade::Sfml*
 */
extern "C" arcade::Sfml *entryPoint() { return new arcade::Sfml(); }
