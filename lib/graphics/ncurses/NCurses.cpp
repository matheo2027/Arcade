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
  initscr(); // Initialize the screen for ncurses
  cbreak();  // Disable line buffering
  noecho();  // Do not echo input characters
  // Create a new window
  int height = 10;
  int width = 30;
  int starty = (LINES - height) / 2;
  int startx = (COLS - width) / 2;
  WINDOW *win = newwin(height, width, starty, startx);

  refresh(); // Refresh the screen to reflect changes
  this->_window = win;
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

void arcade::NCurses::displayMenu()
{
  // Initialize NCurses
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Initialize colors if supported
  if (has_colors()) {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
  }

  // Render the menu
  while (1) {
    clear();

    // Print graphical library options
    attron(COLOR_PAIR(1));
    printw("Select Graphical Library:\n");
    for (size_t i = 0; i < 3; ++i) {
      if (i == this->getCoreModule()->getMenuData().indexGraphic) {
        attron(COLOR_PAIR(2));
        printw("-> ");
      } else {
        attron(COLOR_PAIR(1));
        printw("   ");
      }
      printw("%s\n",
             this->getCoreModule()->getMenuData()._graphicLibList[i].c_str());
    }

    // Print game options
    attron(COLOR_PAIR(1));
    printw("\nSelect Game:\n");
    for (size_t i = 0; i < 2; ++i) {
      if (i == this->getCoreModule()->getMenuData().indexGame) {
        attron(COLOR_PAIR(2));
        printw("-> ");
      } else {
        attron(COLOR_PAIR(1));
        printw("   ");
      }
      printw("%s\n",
             this->getCoreModule()->getMenuData()._gameLibList[i].c_str());
    }

    // Print legend
    attron(COLOR_PAIR(1));
    printw("%s", this->getCoreModule()->getMenuData()._description.c_str());

    // Refresh the screen
    refresh();

    // Handle user input
    int ch = getch();
    switch (ch) {
    case KEY_UP:
      this->getCoreModule()->handleKeyEvent(arcade::KeyboardInput::UP);
      break;
    case KEY_DOWN:
      this->getCoreModule()->handleKeyEvent(
          arcade::KeyboardInput::DOWN);
      break;
    case '\t': // TAB key
      this->getCoreModule()->handleKeyEvent(
          arcade::KeyboardInput::TAB);
      break;
    case '\n': // ENTER key
      this->getCoreModule()->handleKeyEvent(
          arcade::KeyboardInput::ENTER);
      return;
    }

    // Check for exit condition
    if (ch == 'q' || ch == 'Q')
      break;
  }

  // Clean up NCurses
  endwin();
}

void arcade::NCurses::displayGame()
{
  // Initialize NCurses
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Initialize colors if supported
  if (has_colors()) {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
  }

  // Render the menu
  while (1) {
    clear();

    // Refresh the screen
    refresh();

    // Handle user input
    int ch = getch();
    // Check for exit condition

    if (ch == 'q' || ch == 'Q') {
      this->getCoreModule()->handleKeyEvent(
          arcade::KeyboardInput::CROSS);
      break;
    }
  }

  // Clean up NCurses
  endwin();
}

void arcade::NCurses::display()
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
 * @brief entry point
 *
 */
extern "C" std::unique_ptr<arcade::IDisplayModule> entryPoint()
{
  return std::make_unique<arcade::NCurses>();
}

extern "C" arcade::ModuleType getType()
{
  return arcade::ModuleType::GRAPHIC;
}

extern "C" std::string getName()
{
  return "ncurses";
}