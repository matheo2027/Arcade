/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCurses
*/

#include "NCurses.hpp"
#include "Error.hpp"

arcade::NCurses::NCurses() : arcade::IModule(), arcade::ADisplayModule() {}

arcade::NCurses::~NCurses() {}

void arcade::NCurses::display()
{
  switch (this->getDisplayStatus()) {
  case arcade::ADisplayModule::DisplayStatus::RUNNING:
    /* code */
    break;
  default:
    break;
  }
}

void arcade::NCurses::init() {
  initscr(); // Initialize the screen for ncurses
  cbreak();  // Disable line buffering
  noecho();  // Do not echo input characters
  // Create a new window
  int height = 10;
  int width = 30;
  int starty =
      (LINES - height) / 2; // Calculate vertical position to center the window
  int startx =
      (COLS - width) / 2; // Calculate horizontal position to center the window
  WINDOW *win = newwin(height, width, starty, startx); // Create a new window

  refresh(); // Refresh the screen to reflect changes
  this->_window = win;
}

void arcade::NCurses::stop() {

  WINDOW *win = static_cast<WINDOW *>(this->_window);
  win = nullptr;
  if (win == nullptr) {
    try {
      throw NoWindowException("No window to stop");
    } catch (NoWindowException &e) {
      std::cerr << e.what() << std::endl;
    }
  }
  delwin(win); // Delete the window
  endwin();    // Restore normal terminal behavior
}

arcade::IModule::LibName arcade::NCurses::getName() const
{
  return arcade::IModule::LibName::NCURSES;
}

/**
 * @brief entry point
 *
 */
extern "C" arcade::NCurses *entryPoint() { return new arcade::NCurses(); }