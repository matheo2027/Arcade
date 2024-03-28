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
arcade::Sfml::Sfml() : arcade::ADisplayModule()
{
  std::cout << "Sfml created" << std::endl;
  this->_window.create(sf::VideoMode(1920, 1080), "Arcade");
  this->_window.setFramerateLimit(60);
  this->_window.clear(sf::Color::Black);
  this->_window.display();
}

/**
 * @brief Destroy the arcade::Sfml::Sfml object
 *
 */
arcade::Sfml::~Sfml()
{
  std::cout << "Sfml destroyed" << std::endl;
  this->_window.close();
}

void arcade::Sfml::clearWindow() { this->_window.clear(sf::Color::Black); }

void arcade::Sfml::drawSprite(std::pair<char, std::string> sprite,
                              int x,
                              int y,
                              int width,
                              int height)
{
  sf::Texture texture;
  if (!texture.loadFromFile(sprite.second)) {
    // Handle error
    std::cerr << "Failed to load texture: " << sprite.second << std::endl;
    return;
  }

  sf::Sprite mySprite;
  mySprite.setTexture(texture);
  mySprite.setPosition(x, y);

  // Calculate the scale factors
  float scaleX = static_cast<float>(width) / texture.getSize().x;
  float scaleY = static_cast<float>(height) / texture.getSize().y;
  mySprite.setScale(scaleX, scaleY);

  this->_window.draw(mySprite);
}

void arcade::Sfml::displayWindow() { this->_window.display(); }

void arcade::Sfml::drawText(const std::string text, int x, int y, int size)
{
  sf::Font font;
  if (!font.loadFromFile("assets/default/font/font1.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
    return;
  }
  sf::Text sfText;
  sfText.setFont(font);
  sfText.setCharacterSize(size);
  sfText.setFillColor(sf::Color::White);
  sfText.setPosition(x, y);
  sfText.setString(text);
  this->_window.draw(sfText);
}

arcade::KeyboardInput arcade::Sfml::getInput()
{
  sf::Event event;

  while (this->_window.pollEvent(event)) {
    switch (event.type) {
    case sf::Event::KeyPressed:
      switch (event.key.code) {

      case sf::Keyboard::Up:
        return arcade::KeyboardInput::UP;
      case sf::Keyboard::Down:
        return arcade::KeyboardInput::DOWN;
      case sf::Keyboard::Left:
        return arcade::KeyboardInput::LEFT;
      case sf::Keyboard::Right:
        return arcade::KeyboardInput::RIGHT;
      case sf::Keyboard::Space:
        return arcade::KeyboardInput::SPACE;
      case sf::Keyboard::Escape:
        return arcade::KeyboardInput::ESCAPE;
      case sf::Keyboard::Return:
        return arcade::KeyboardInput::ENTER;
      case sf::Keyboard::Tab:
        return arcade::KeyboardInput::TAB;
        break;
      default:
        break;
      }
      break;
    case sf::Event::Closed:
      return arcade::KeyboardInput::CROSS;
    default:
      break;
    }
  }
  return arcade::KeyboardInput::NONE;
}

/**
 * @brief entry point for the library
 *
 * @return arcade::Sfml*
 */
extern "C" std::unique_ptr<arcade::IDisplayModule> entryPoint()
{
  return std::make_unique<arcade::Sfml>();
}

extern "C" arcade::ModuleType getType() { return arcade::ModuleType::GRAPHIC; }

extern "C" std::string getName() { return "sfml"; }
