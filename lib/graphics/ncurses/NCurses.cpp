/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NCurses
*/

#include "NCurses.hpp"
#include "Error.hpp"

arcade::NCurses::NCurses() : arcade::ADisplayModule()
{
  std::cout << "NCurses created" << std::endl;
  initscr();             // Initialize the screen for ncurses
  cbreak();              // Disable line buffering
  noecho();              // Do not echo input characters
  keypad(stdscr, TRUE);  // Enable special keys
  nodelay(stdscr, TRUE); // Do not block when reading input
  curs_set(0);           // Hide the cursor
  // Create a new window
  int height = COLS;
  int width = LINES;

  this->_window = newwin(height, width, 0, 0);
  refresh(); // Refresh the screen to reflect changes
}

arcade::NCurses::~NCurses()
{
  std::cout << "NCurses destroyed" << std::endl;

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

void arcade::NCurses::clearWindow()
{
  wclear(this->_window); // Clear the window
}

void arcade::NCurses::drawSprite(
    std::pair<char, std::string> sprite, int x, int y, int width, int height)
{
  // Draw the sprite at the specified position
  mvwprintw(this->_window, y, x, &(sprite.first));
}

void arcade::NCurses::drawText(const std::string text, int x, int y, int size)
{
  // Draw the text at the specified position
  mvwprintw(this->_window, y, x, text.c_str());
}

void arcade::NCurses::displayWindow()
{
  // Refresh the window
  wrefresh(this->_window);
}

arcade::KeyboardInput arcade::NCurses::getInput()
{
  // Get user input
  int ch = getch();
  switch (ch) {
  case KEY_UP:
    return arcade::KeyboardInput::UP;
  case KEY_DOWN:
    return arcade::KeyboardInput::DOWN;
  case KEY_LEFT:
    return arcade::KeyboardInput::LEFT;
  case KEY_RIGHT:
    return arcade::KeyboardInput::RIGHT;
  case '\t':
    return arcade::KeyboardInput::TAB;
  case '\n':
    return arcade::KeyboardInput::ENTER;
  case 'q':
    return arcade::KeyboardInput::CROSS;
  default:
    return arcade::KeyboardInput::NONE;
  }
}

/**
 * @brief entry point
 *
 */
extern "C" std::unique_ptr<arcade::IDisplayModule> entryPoint()
{
  return std::make_unique<arcade::NCurses>();
}

extern "C" arcade::ModuleType getType() { return arcade::ModuleType::GRAPHIC; }

extern "C" std::string getName() { return "ncurses"; }
