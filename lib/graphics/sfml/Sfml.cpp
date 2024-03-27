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

void arcade::Sfml::displayMenu()
{
  // Font loading
  sf::Font font;
  if (!font.loadFromFile("assets/default/font/font1.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
    return;
  }

  // Text setup
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setPosition(20.f, 20.f);

  // Render the menu
  while (this->_window.isOpen()) {
    sf::Event event;
    while (this->_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        this->getCoreModule()->handleKeyEvent(
            arcade::KeyboardInput::CROSS);
      }
      if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
          this->getCoreModule()->handleKeyEvent(
              arcade::KeyboardInput::UP);
          break;
        case sf::Keyboard::Down:
          this->getCoreModule()->handleKeyEvent(
              arcade::KeyboardInput::DOWN);
          break;
        case sf::Keyboard::Tab:
          this->getCoreModule()->handleKeyEvent(
              arcade::KeyboardInput::TAB);
          break;
        case sf::Keyboard::Return:
          this->getCoreModule()->handleKeyEvent(
              arcade::KeyboardInput::ENTER);
          return;
        }
      }
    }

    // Update text
    std::string menuText = "Select Graphical Library:\n";
    for (size_t i = 0;
         i < this->getCoreModule()->getMenuData()._graphicLibList.size();
         ++i) {
      if (i == this->getCoreModule()->getMenuData().indexGraphic) {
        menuText += "-> " +
                    this->getCoreModule()->getMenuData()._graphicLibList[i] +
                    "\n";
      } else {
        menuText += "   " +
                    this->getCoreModule()->getMenuData()._graphicLibList[i] +
                    "\n";
      }
    }
    menuText += "\nSelect Game:\n";
    for (size_t i = 0;
         i < this->getCoreModule()->getMenuData()._gameLibList.size();
         ++i) {
      if (i == this->getCoreModule()->getMenuData().indexGame) {
        menuText +=
            "-> " + this->getCoreModule()->getMenuData()._gameLibList[i] + "\n";
      } else {
        menuText +=
            "   " + this->getCoreModule()->getMenuData()._gameLibList[i] + "\n";
      }
    }
    menuText += this->getCoreModule()->getMenuData()._description;
    text.setString(menuText);

    // Draw
    this->_window.clear(sf::Color::Black);
    this->_window.draw(text);
    this->_window.display();
  }
}

void arcade::Sfml::displayGame()
{
  // Render the menu
  while (this->_window.isOpen()) {
    sf::Event event;
    while (this->_window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        this->getCoreModule()->handleKeyEvent(
            arcade::KeyboardInput::CROSS);
        this->_window.close();
        return;
      }
    }

    // Draw
    this->_window.clear(sf::Color::Black);
    this->_window.display();
  }
}

void arcade::Sfml::display()
{
  switch (this->getDisplayStatus()) {
  case arcade::ADisplayModule::DisplayStatus::RUNNING:
    this->displayGame();
    break;
  case arcade::ADisplayModule::DisplayStatus::SELECTION:
    this->displayMenu();
    break;
  default:
    break;
  }
}

/**
 * @brief get the keyboard input
 *
 * @return arcade::IModule::KeyboardInput
 */
// arcade::IModule::KeyboardInput arcade::Sfml::getInput()
// {
//   sf::RenderWindow *window = static_cast<sf::RenderWindow *>(this->_window);
//   if (window == nullptr) {
//     try {
//       throw NoWindowException("No window to stop");
//     } catch (NoWindowException &e) {
//       std::cerr << e.what() << std::endl;
//     }
//   }
//   sf::Event event;

//   while (window->pollEvent(event)) {
//     switch (event.type) {
//     case sf::Event::KeyPressed:
//       switch (event.key.code) {
//         // case sf::Event::Closed:

//       case sf::Keyboard::Up:
//         return arcade::IModule::KeyboardInput::UP;
//       case sf::Keyboard::Down:
//         return arcade::IModule::KeyboardInput::DOWN;
//       case sf::Keyboard::Left:
//         return arcade::IModule::KeyboardInput::LEFT;
//       case sf::Keyboard::Right:
//         return arcade::IModule::KeyboardInput::RIGHT;
//       case sf::Keyboard::Space:
//         return arcade::IModule::KeyboardInput::SPACE;
//       case sf::Keyboard::Escape:
//         return arcade::IModule::KeyboardInput::ESCAPE;
//       default:
//         break;
//       }
//       break;

//     default:
//       break;
//     }
//   }
//   return arcade::IModule::KeyboardInput::NONE;
// }

/**
 * @brief entry point for the library
 *
 * @return arcade::Sfml*
 */
extern "C" std::unique_ptr<arcade::IDisplayModule> entryPoint()
{
  return std::make_unique<arcade::Sfml>();
}

extern "C" arcade::ModuleType getType()
{
  return arcade::ModuleType::GRAPHIC;
}

extern "C" std::string getName()
{
  return "sfml";
}