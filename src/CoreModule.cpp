/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#include "CoreModule.hpp"
#include "Error.hpp"
#include <unistd.h>

/**
 * @brief Construct a new arcade::Core Module::Core Module object
 *
 */
arcade::CoreModule::CoreModule()
{
  this->_coreStatus = CoreStatus::SELECTION;
  this->_gameModule = nullptr;
  this->_graphicModule = nullptr;
  // MenuData
  this->_menuData._username = "";
  this->_menuData.indexGame = 0;
  this->_menuData.indexGraphic = 0;
  this->_menuData._description = "\nLegend:\nPress UP/DOWN to navigate\n\
Press ENTER to confirm the choice\n\
Press TAB to switch between Graphical Library and Game selection";
  this->_menuData._type = arcade::ICoreModule::MenuSelection::USERNAME;
}

/**
 * @brief Destroy the arcade::Core Module::Core Module object
 *
 */
arcade::CoreModule::~CoreModule()
{
  std::cout << "CoreModule destroyed" << std::endl;
  if (this->_gameModule) {
    delete this->_gameModule;
  }
  if (this->_graphicModule) {
    delete this->_graphicModule;
  }
}

/**
 * @brief get the status of the core module
 *
 * @return CoreStatus
 */
void arcade::CoreModule::setCoreStatus(CoreStatus status)
{
  this->_coreStatus = status;
}

/**
 * @brief get the status of the core module
 *
 * @return CoreStatus
 */
arcade::CoreModule::CoreStatus arcade::CoreModule::getCoreStatus() const
{
  return this->_coreStatus;
}

/**
 * @brief get the display module
 *
 * @return arcade::IDisplayModule *
 */
arcade::IDisplayModule *arcade::CoreModule::getGraphicModule()
{
  return this->_graphicModule;
}

/**
 * @brief get the game module
 *
 * @return arcade::IGameModule *
 */
arcade::IGameModule *arcade::CoreModule::getGameModule()
{
  return this->_gameModule;
}

/**
 * @brief set graphic or game module to the core module
 *
 * @param module to set
 * @param type of the module (graphic or game)
 */

void arcade::CoreModule::setGraphicModule(
    std::unique_ptr<arcade::IDisplayModule> module)
{
  this->_graphicModule = module.release();
}

void arcade::CoreModule::setGameModule(
    std::unique_ptr<arcade::IGameModule> module)
{
  this->_gameModule = module.release();
}

void arcade::CoreModule::addLibList(std::string pathLib)
{
  DLLoader<arcade::ModuleType> loader(pathLib);
  arcade::ModuleType module = loader.getInstance("getType");
  switch (module) {
  case arcade::ModuleType::GAME:
    this->_menuData._gameLibList.push_back(pathLib);
    break;
  case arcade::ModuleType::GRAPHIC:
    this->_menuData._graphicLibList.push_back(pathLib);
    break;
  default:
    throw std::exception();
  }
}

/**
 * @brief get the list of libraries in the given path
 *
 * @param pathLib path to the libraries
 */
void arcade::CoreModule::getLib(std::string pathLib)
{
  std::vector<std::string> matchedFiles;
  DIR *dir;
  struct dirent *entry;

  dir = opendir(pathLib.c_str());
  if (dir == nullptr) {
    perror("opendir");
    try {
      throw OpendirException("Could not open directory");
    } catch (OpendirException &e) {
      std::cerr << e.what() << std::endl;
    }
  }
  while ((entry = readdir(dir)) != nullptr) {
    if (strncmp(entry->d_name, "arcade_", strlen("arcade_")) == 0 &&
        strncmp(&(entry->d_name[strlen(entry->d_name) - 3]), ".so", 3) == OK) {
      matchedFiles.push_back(std::string(entry->d_name));
    }
  }
  closedir(dir);

  for (std::string file : matchedFiles) {
    file = pathLib + file;
    try {
      this->addLibList(file);
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
      throw std::exception();
    }
  }
}

void arcade::CoreModule::loadLib(std::string pathLib)
{
  std::cout << "start Load lib" << pathLib << std::endl;
  DLLoader<arcade::ModuleType> loaderTypeModule(pathLib);
  arcade::ModuleType module = loaderTypeModule.getInstance("getType");
  DLLoader<std::unique_ptr<arcade::IDisplayModule>> loaderGraphic(pathLib);
  DLLoader<std::unique_ptr<arcade::IGameModule>> loaderGame(pathLib);
  switch (module) {
  case arcade::ModuleType::GAME:
    if (this->_gameModule) {
      DLLoader<std::string> loaderTypeModule(pathLib);
      std::string moduleName = loaderTypeModule.getInstance("getName");
      if (moduleName == this->_graphicModule->getName())
        return;
      delete this->_gameModule;
    }
    this->_gameModule =
        std::move(loaderGame.getInstance("entryPoint")).release();
    this->_gameModule->setCoreModule(this);
    this->_gameModule->init();
    break;
  case arcade::ModuleType::GRAPHIC:
    if (this->_graphicModule) {
      DLLoader<std::string> loaderTypeModule(pathLib);
      std::string moduleName = loaderTypeModule.getInstance("getName");
      if (moduleName == this->_graphicModule->getName())
        return;
      delete this->_graphicModule;
    }
    this->_graphicModule =
        std::move(loaderGraphic.getInstance("entryPoint")).release();
    this->_graphicModule->setCoreModule(this);
    break;
  default:
    try {
      throw BadModuleTypeException("Bad module type");
    } catch (BadModuleTypeException &e) {
      std::cerr << e.what() << std::endl;
    }
    break;
  }
  this->_menuData.indexGame = this->_menuData._gameLibList.size() / 2;
  this->_menuData.indexGraphic = this->_menuData._graphicLibList.size() / 2;
}

void arcade::CoreModule::launchSelection()
{
  if (this->_menuData._username == "" ||
      this->_menuData._username == "Please enter a username") {
    this->_menuData._username = "Please enter a username";
    this->_menuData._type = arcade::ICoreModule::MenuSelection::USERNAME;
  } else {
    this->loadLib(this->_menuData._gameLibList[this->_menuData.indexGame]);
    this->loadLib(
        this->_menuData._graphicLibList[this->_menuData.indexGraphic]);
    this->_coreStatus = CoreStatus::RUNNING;
  }
}

void arcade::CoreModule::addCharUsername(char c)
{
  if (this->_menuData._username == "Please enter a username")
    this->_menuData._username = "";
  this->_menuData._username += c;
}

void arcade::CoreModule::handleKeySelection(arcade::KeyboardInput key)
{
  switch (this->_menuData._type) {
  case arcade::ICoreModule::MenuSelection::USERNAME:
    switch (key) {
    case arcade::KeyboardInput::A:
      addCharUsername('a');
      break;
    case arcade::KeyboardInput::B:
      addCharUsername('b');
      break;
    case arcade::KeyboardInput::C:
      addCharUsername('c');
      break;
    case arcade::KeyboardInput::D:
      addCharUsername('d');
      break;
    case arcade::KeyboardInput::E:
      addCharUsername('e');
      break;
    case arcade::KeyboardInput::F:
      addCharUsername('f');
      break;
    case arcade::KeyboardInput::G:
      addCharUsername('g');
      break;
    case arcade::KeyboardInput::H:
      addCharUsername('h');
      break;
    case arcade::KeyboardInput::I:
      addCharUsername('i');
      break;
    case arcade::KeyboardInput::J:
      addCharUsername('j');
      break;
    case arcade::KeyboardInput::K:
      addCharUsername('k');
      break;
    case arcade::KeyboardInput::L:
      addCharUsername('l');
      break;
    case arcade::KeyboardInput::M:
      addCharUsername('m');
      break;
    case arcade::KeyboardInput::N:
      addCharUsername('n');
      break;
    case arcade::KeyboardInput::O:
      addCharUsername('o');
      break;
    case arcade::KeyboardInput::P:
      addCharUsername('p');
      break;
    case arcade::KeyboardInput::Q:
      addCharUsername('q');
      break;
    case arcade::KeyboardInput::R:
      addCharUsername('r');
      break;
    case arcade::KeyboardInput::S:
      addCharUsername('s');
      break;
    case arcade::KeyboardInput::T:
      addCharUsername('t');
      break;
    case arcade::KeyboardInput::U:
      addCharUsername('u');
      break;
    case arcade::KeyboardInput::V:
      addCharUsername('v');
      break;
    case arcade::KeyboardInput::W:
      addCharUsername('w');
      break;
    case arcade::KeyboardInput::X:
      addCharUsername('x');
      break;
    case arcade::KeyboardInput::Y:
      addCharUsername('y');
      break;
    case arcade::KeyboardInput::Z:
      addCharUsername('z');
      break;
    case arcade::KeyboardInput::ENTER:
      this->launchSelection();
      break;
    case arcade::KeyboardInput::BACKSPACE:
      if (!this->_menuData._username.empty())
        this->_menuData._username.pop_back();
      break;
    case arcade::KeyboardInput::TAB:
      this->_menuData._type = arcade::ICoreModule::MenuSelection::GRAPHIC;
      break;
    case arcade::KeyboardInput::ESCAPE:
      this->_coreStatus = CoreStatus::EXIT;
      break;
    case arcade::KeyboardInput::CROSS:
      this->_coreStatus = CoreStatus::EXIT;
      break;
    }
    break;
  case arcade::ICoreModule::MenuSelection::GRAPHIC:
    switch (key) {
    case arcade::KeyboardInput::UP:
      this->_menuData._graphicLibList.push_back(
          this->_menuData._graphicLibList.front());
      this->_menuData._graphicLibList.erase(
          this->_menuData._graphicLibList.begin());
      break;
    case arcade::KeyboardInput::DOWN:
      this->_menuData._graphicLibList.insert(
          this->_menuData._graphicLibList.begin(),
          this->_menuData._graphicLibList.back());
      this->_menuData._graphicLibList.pop_back();
      break;
    case arcade::KeyboardInput::ENTER:
      this->launchSelection();
      break;
    case arcade::KeyboardInput::TAB:
      this->_menuData._type = arcade::ICoreModule::MenuSelection::GAME;
      break;
    case arcade::KeyboardInput::ESCAPE:
      this->_coreStatus = CoreStatus::EXIT;
      break;
    case arcade::KeyboardInput::CROSS:
      this->_coreStatus = CoreStatus::EXIT;
      break;
    }
    break;
  case arcade::ICoreModule::MenuSelection::GAME:
    switch (key) {
    case arcade::KeyboardInput::UP:
      this->_menuData._gameLibList.push_back(
          this->_menuData._gameLibList.front());
      this->_menuData._gameLibList.erase(this->_menuData._gameLibList.begin());
      break;
    case arcade::KeyboardInput::DOWN:
      this->_menuData._gameLibList.insert(this->_menuData._gameLibList.begin(),
                                          this->_menuData._gameLibList.back());
      this->_menuData._gameLibList.pop_back();
      break;
    case arcade::KeyboardInput::ENTER:
      this->launchSelection();
      break;
    case arcade::KeyboardInput::TAB:
      this->_menuData._type = arcade::ICoreModule::MenuSelection::USERNAME;
      break;
    case arcade::KeyboardInput::ESCAPE:
      this->_coreStatus = CoreStatus::EXIT;
      break;
    case arcade::KeyboardInput::CROSS:
      this->_coreStatus = CoreStatus::EXIT;
      break;
    }
    break;
  default:
    std::cerr << "Bad MenuSelection" << std::endl;
    break;
  }
}

void arcade::CoreModule::handleKeyRunning(arcade::KeyboardInput key)
{
  switch (key) {
  case arcade::KeyboardInput::CROSS:
    this->_coreStatus = CoreStatus::EXIT;
    break;
  case arcade::KeyboardInput::Q:
    this->_coreStatus = CoreStatus::EXIT;
    break;
  case arcade::KeyboardInput::ESCAPE:
    this->_coreStatus = CoreStatus::SELECTION;
    break;
  }
}

void arcade::CoreModule::handleKeyEvent(arcade::KeyboardInput key)
{
  switch (this->_coreStatus) {
  case CoreStatus::SELECTION:
    this->handleKeySelection(key);
    break;
  case CoreStatus::RUNNING:
    this->handleKeyRunning(key);
    break;
  default:
    throw std::exception();
  }
}

/**
 * @brief get the menu data
 *
 * @return arcade::IModule::MenuData
 */
arcade::ICoreModule::MenuData arcade::CoreModule::getMenuData() const
{
  return this->_menuData;
}

/**
 * @brief get the game data
 *
 * @return arcade::IModule::GameData
 */
arcade::GameData arcade::CoreModule::getGameData() const
{
  return this->_gameData;
}

/**
 * @brief set the game data
 *
 * @param gameData game data to set
 */
void arcade::CoreModule::setGameData(arcade::GameData gameData)
{
  this->_gameData = gameData;
}

/**
 * @brief core loop
 *
 * @return int
 */
int arcade::CoreModule::coreLoop()
{
  while (this->_coreStatus != CoreStatus::EXIT) {
    switch (this->_coreStatus) {
    case CoreStatus::SELECTION:
      this->selectionLoop();
      break;
    case CoreStatus::RUNNING:
      this->runningLoop();
      break;
    default:
      throw std::exception();
    }
  }
  return 0;
}

/**
 * @brief update selection
 *
 */
void arcade::CoreModule::updateSelection()
{
  std::string selection = "";
  std::string username = "Enter your username :\n";
  std::string graphic = "selected graphic library:\n";
  std::string game = "selected game library:\n";
  username += this->_menuData._username + "\n";
  for (size_t i = 0; i < this->_menuData._graphicLibList.size(); i += 1) {
    if (i == this->_menuData.indexGraphic)
      graphic += "-> " + this->_menuData._graphicLibList[i] + "\n";
    else
      graphic += "   " + this->_menuData._graphicLibList[i] + "\n";
  }
  for (size_t i = 0; i < this->_menuData._gameLibList.size(); i += 1) {
    if (i == this->_menuData.indexGame)
      game += "-> " + this->_menuData._gameLibList[i] + "\n";
    else
      game += "   " + this->_menuData._gameLibList[i] + "\n";
  }
  selection = username + "\n" + graphic + "\n" + game + "\n" +
              this->_menuData._description;

  this->getGraphicModule()->clearWindow();
  this->getGraphicModule()->drawText(selection, 0, 0, 20);
  this->getGraphicModule()->displayWindow();
}

/**
 * @brief selection loop
 *
 */
void arcade::CoreModule::selectionLoop()
{
  this->updateSelection();
  this->updateSelection();
  std::cout << "selection loop" << std::endl;
  while (this->_coreStatus == CoreStatus::SELECTION) {
    arcade::KeyboardInput actualKeyPress = this->getGraphicModule()->getInput();
    this->handleKeyEvent(actualKeyPress);
    if (actualKeyPress != arcade::KeyboardInput::NONE)
      this->updateSelection();
    usleep(1);
  }
}

void arcade::CoreModule::updateRunning()
{
  std::pair<char, std::string> sprite;
  this->getGameModule()->updateGame();
  this->getGraphicModule()->clearWindow();
  // draw sprites on map
  for (size_t i = 0; i < this->getGameData().display_info.size(); i += 1) {
    for (size_t j = 0; j < this->getGameData().display_info[i].size(); j += 1) {
      sprite.first = this->getGameData().display_info[i][j];
      sprite.second = this->getGameData()
                          .sprite_value[this->getGameData().display_info[i][j]];
      this->getGraphicModule()->drawSprite(sprite, j, i, 30, 30);
    }
  }
  this->getGraphicModule()->displayWindow();
}

/**
 * @brief running loop
 *
 */
void arcade::CoreModule::runningLoop()
{
  arcade::KeyboardInput input;
  this->getGraphicModule()->clearWindow();
  while (this->_coreStatus == CoreStatus::RUNNING) {
    this->updateRunning();
    input = this->getGraphicModule()->getInput();
    this->handleKeyEvent(input);
    this->getGameModule()->handdleKeyEvents(input);
  }
}