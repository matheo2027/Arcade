/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#include "CoreModule.hpp"
#include "Error.hpp"

/**
 * @brief Construct a new arcade::Core Module::Core Module object
 *
 */
arcade::CoreModule::CoreModule() : arcade::IModule()
{
  this->_coreStatus = CoreStatus::SELECTION;
  this->_gameModule = nullptr;
  this->_graphicModule = nullptr;
  this->_menuData._description = "\nLegend:\nPress UP/DOWN to navigate\n\
Press ENTER to confirm the choice\n\
Press TAB to switch between Graphical Library and Game selection";
  this->_menuData.indexGame = 0;
  this->_menuData.indexGraphic = 0;
  this->_menuData._type = arcade::IModule::ModuleType::GRAPHIC;
}

/**
 * @brief Destroy the arcade::Core Module::Core Module object
 *
 */
arcade::CoreModule::~CoreModule() { this->stop(); }

/**
 * @brief load the libraries in the given path
 *
 * @param pathLib path to the libraries
 */
void arcade::CoreModule::init() {}

/**
 * @brief stop the core module
 *
 */
void arcade::CoreModule::stop()
{
  if (this->_gameModule != nullptr) {
    this->_gameModule->stop();
    delete (this->_gameModule);
    this->_gameModule = nullptr;
  }
  if (this->_gameModule != nullptr) {
    this->_graphicModule->stop();
    delete (this->_graphicModule);
    this->_graphicModule = nullptr;
  }
}

/**
 * @brief get the name of the library
 *
 * @return arcade::IModule::LibName
 */
arcade::IModule::LibName arcade::CoreModule::getName() const
{
  return arcade::IModule::LibName::UNKNOWN;
}

/**
 * @brief get the type of the library
 *
 * @return arcade::IModule::ModuleType
 */
arcade::IModule::ModuleType arcade::CoreModule::getType() const
{
  return arcade::IModule::ModuleType::CORE;
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
void arcade::CoreModule::setModule(arcade::IModule *module,
                                   arcade::IModule::ModuleType type)
{
  switch (type) {
  case arcade::IModule::ModuleType::GAME:
    this->_gameModule = dynamic_cast<arcade::IGameModule *>(module);
    break;
  case arcade::IModule::ModuleType::GRAPHIC:
    this->_graphicModule = dynamic_cast<arcade::IDisplayModule *>(module);
    break;
  default:
    try {
      throw BadModuleTypeException("Bad module type");
    } catch (BadModuleTypeException &e) {
      std::cerr << e.what() << std::endl;
    }
  }
  return;
}

void arcade::CoreModule::addLibList(std::string pathLib)
{
  DLLoader<arcade::IModule> loader(pathLib);
  arcade::IModule *module = loader.getInstance("entryPoint");
  if (module == nullptr)
    throw std::exception();
  switch (module->getType()) {
  case arcade::IModule::ModuleType::GAME:
    this->_menuData._gameLibList.push_back(pathLib);
    break;
  case arcade::IModule::ModuleType::GRAPHIC:
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
  DLLoader<arcade::IModule> loader(pathLib);
  arcade::IModule *module = loader.getInstance("entryPoint");
  if (module == nullptr)
    try {
      throw NoModuleLoadedException("No module loaded");
    } catch (NoModuleLoadedException &e) {
      std::cerr << e.what() << std::endl;
    }
  if (module->getType() == arcade::IModule::ModuleType::GAME) {
    if (this->_gameModule != nullptr) {
      this->_gameModule->stop();
      delete (this->_gameModule);
    }
    this->_gameModule = dynamic_cast<arcade::IGameModule *>(module);
    this->_gameModule->setCoreModule(this);
    this->_gameModule->init();
  } else if (module->getType() == arcade::IModule::ModuleType::GRAPHIC) {
    if (this->_gameModule != nullptr) {
      this->_graphicModule->stop();
      delete (this->_graphicModule);
    }
    this->_graphicModule = dynamic_cast<arcade::IDisplayModule *>(module);
    this->_graphicModule->setCoreModule(this);
    this->_graphicModule->init();
  } else {
    try {
      throw BadModuleTypeException("Bad module type");
    } catch (BadModuleTypeException &e) {
      std::cerr << e.what() << std::endl;
    }
  }
  this->_menuData.indexGame = this->_menuData._gameLibList.size() / 2;
  this->_menuData.indexGraphic = this->_menuData._graphicLibList.size() / 2;
}

void arcade::CoreModule::handleKeySelection(arcade::IModule::KeyboardInput key)
{
  switch (key) {
  case arcade::IModule::KeyboardInput::UP:
    if (this->_menuData._type == arcade::IModule::ModuleType::GRAPHIC) {
      this->_menuData._graphicLibList.push_back(
          this->_menuData._graphicLibList.front());
      this->_menuData._graphicLibList.erase(
          this->_menuData._graphicLibList.begin());
    } else {
      this->_menuData._gameLibList.push_back(
          this->_menuData._gameLibList.front());
      this->_menuData._gameLibList.erase(this->_menuData._gameLibList.begin());
    }
    break;
  case arcade::IModule::KeyboardInput::DOWN:
    if (this->_menuData._type == arcade::IModule::ModuleType::GRAPHIC) {
      this->_menuData._graphicLibList.insert(
          this->_menuData._graphicLibList.begin(),
          this->_menuData._graphicLibList.back());
      this->_menuData._graphicLibList.pop_back();
    } else {
      this->_menuData._gameLibList.insert(this->_menuData._gameLibList.begin(),
                                          this->_menuData._gameLibList.back());
      this->_menuData._gameLibList.pop_back();
    }
    break;
  case arcade::IModule::KeyboardInput::ENTER:
    if (this->_menuData._gameLibList.size() == 0 ||
        this->_menuData._graphicLibList.size() == 0)
      throw std::exception();
    this->loadLib(this->_menuData._gameLibList[this->_menuData.indexGame]);
    this->loadLib(
        this->_menuData._graphicLibList[this->_menuData.indexGraphic]);
    this->_coreStatus = CoreStatus::RUNNING;
    this->getGraphicModule()->setDisplayStatus(
        arcade::IDisplayModule::DisplayStatus::RUNNING);
    break;
  case arcade::IModule::KeyboardInput::TAB:
    if (this->_menuData._type == arcade::IModule::ModuleType::GRAPHIC)
      this->_menuData._type = arcade::IModule::ModuleType::GAME;
    else
      this->_menuData._type = arcade::IModule::ModuleType::GRAPHIC;
    break;
  case arcade::IModule::KeyboardInput::CROSS:
    this->_coreStatus = CoreStatus::EXIT;
    break;
  default:
    break;
  }
}

void arcade::CoreModule::handleKeyRunning(arcade::IModule::KeyboardInput key)
{
  switch (key) {
    case arcade::IModule::KeyboardInput::UP:
      this->_keyInput = arcade::IModule::KeyboardInput::UP;
      break;
  // case arcade::IModule::KeyboardInput::ESCAPE:
  //   this->_coreStatus = CoreStatus::SELECTION;
  //   break;
  case arcade::IModule::KeyboardInput::CROSS:
    this->_coreStatus = CoreStatus::EXIT;
    break;
  default:
    break;
  }
}

void arcade::CoreModule::handleKeyEvent(arcade::IModule::KeyboardInput key)
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
arcade::IModule::MenuData arcade::CoreModule::getMenuData() const
{
  return this->_menuData;
}

/**
 * @brief get the game data
 *
 * @return arcade::IModule::GameData
 */
arcade::IModule::GameData arcade::CoreModule::getGameData() const
{
  return this->_gameData;
}

/**
 * @brief set the game data
 *
 * @param gameData game data to set
 */
void arcade::CoreModule::setGameData(arcade::IModule::GameData gameData)
{
  this->_gameData = gameData;
}

void arcade::CoreModule::setKeyboardInput(arcade::IModule::KeyboardInput key)
{
  this->_keyInput = key;
}

arcade::IModule::KeyboardInput arcade::CoreModule::getKeyboardInput()
{
  return this->_keyInput;
}
