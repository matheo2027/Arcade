/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#include <CoreModule.hpp>
#include <Error.hpp>
#include <fcntl.h>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
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
Press TAB to switch to the next section";
  this->_menuData._type = arcade::ICoreModule::MenuSelection::USERNAME;
  this->_timers.push_back({std::chrono::steady_clock::now(),
                           std::chrono::steady_clock::now(),
                           std::chrono::milliseconds(0)});
  srand(time(NULL));
}

/**
 * @brief Destroy the arcade::Core Module::Core Module object
 *
 */
arcade::CoreModule::~CoreModule()
{
  if (this->_libList.size() > 0) {
    for (auto &loader : arcade::CoreModule::_libList) {
      loader.DLLunloader();
    }
  }
  if (this->_interfaceList.size() > 0) {
    for (auto &loader : arcade::CoreModule::_interfaceList) {
      loader.first.DLLunloader();
      loader.second.DLLunloader();
    }
  }
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
  // arcade::CoreModule::DLLoader<arcade::ModuleType> loader(pathLib);
  arcade::CoreModule::_libList.push_back(DLLoader<arcade::ModuleType>(pathLib));
  arcade::ModuleType module =
      arcade::CoreModule::_libList.back().getInstance("getType");
  // arcade::ModuleType module = loader.getInstance("getType");
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
  arcade::CoreModule::_libList.push_back(
      arcade::CoreModule::DLLoader<arcade::ModuleType>(pathLib));
  arcade::ModuleType module =
      arcade::CoreModule::_libList.back().getInstance("getType");
  arcade::CoreModule::_interfaceList.emplace_back(
      DLLoader<std::unique_ptr<arcade::IDisplayModule>>(pathLib),
      DLLoader<std::unique_ptr<arcade::IGameModule>>(pathLib));
  switch (module) {
  case arcade::ModuleType::GAME:
    if (this->_gameModule) {
      delete this->_gameModule;
    }
    this->_gameModule =
        std::move(arcade::CoreModule::_interfaceList.back().second.getInstance(
                      "entryPoint"))
            .release();
    this->_gameModule->setCoreModule(this);
    this->_gameModule->init();
    break;
  case arcade::ModuleType::GRAPHIC:
    if (this->_graphicModule) {
      arcade::CoreModule::_nameLoader.push_back(DLLoader<std::string>(pathLib));
      // DLLoader<std::string> loaderTypeModule(pathLib);
      std::string moduleName = _nameLoader.back().getInstance("getName");
      if (moduleName == this->_graphicModule->getName())
        return;
      delete this->_graphicModule;
    }
    this->_graphicModule =
        std::move(arcade::CoreModule::_interfaceList.back().first.getInstance(
                      "entryPoint"))
            .release();
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

void arcade::CoreModule::generateScore()
{
  mkdir("scoreArcade", 0777);

  // Create a file
  std::ofstream outputFile;

  for (std::string game_lib_path : this->_menuData._gameLibList) {
    arcade::CoreModule::_nameLoader.push_back(
        DLLoader<std::string>(game_lib_path));
    std::string moduleName = _nameLoader.back().getInstance("getName");
    FILE *fd = fopen(("scoreArcade/" + moduleName + ".txt").c_str(), "r");
    if (fd) {
      fclose(fd);
      break;
    } else {
      outputFile.open("scoreArcade/" + moduleName + ".txt");
      if (!outputFile.is_open()) {
        std::cerr << "Error creating file!" << std::endl;
      }
      outputFile.close();
    }
  }
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
  case arcade::KeyboardInput::D:
    this->_menuData._graphicLibList.push_back(
        this->_menuData._graphicLibList.front());
    this->_menuData._graphicLibList.erase(
        this->_menuData._graphicLibList.begin());
    this->loadLib(
        this->_menuData._graphicLibList[this->_menuData.indexGraphic]);
    break;
  case arcade::KeyboardInput::G:
    this->_menuData._gameLibList.push_back(
        this->_menuData._gameLibList.front());
    this->_menuData._gameLibList.erase(this->_menuData._gameLibList.begin());
    this->loadLib(this->_menuData._gameLibList[this->_menuData.indexGame]);
    break;
  case arcade::KeyboardInput::R:
    this->loadLib(this->_menuData._gameLibList[this->_menuData.indexGame]);
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

std::vector<std::string> split_str(std::string const &str, const char delim)
{
  // create a stream from the string
  std::stringstream s(str);
  std::vector<std::string> out;
  std::string s2;
  while (std::getline(s, s2, delim)) {
    out.push_back(s2); // store the string in s2
  }
  return out;
}

static void generateFocusVersion(std::string &section, int len)
{
  for (int i = 0; i < len; i += 1) {
    section = "#" + section;
  }
  for (int i = 1; i < section.size(); i += 1) {
    if (section[i - 1] == '\n')
      section[i] = '#';
  }
  section.pop_back();
  for (int i = 0; i < len; i += 1) {
    section += "#";
  }
  section += "\n";
}

int max_len_line(std::string str)
{
  int max = 0;
  for (std::string line : split_str(str, '\n')) {
    if (line.size() > max)
      max = line.size();
  }
  return max;
}

std::vector<std::pair<std::string, int>>
getScoreFromFile(std::string moduleName)
{
  std::ifstream file("scoreArcade/" + moduleName + ".txt");
  std::string line;
  std::vector<std::pair<std::string, int>> all_file;
  if (file.is_open()) {
    while (std::getline(file, line)) {
      if (!line.empty()) {
        std::vector<std::string> line_split = split_str(line, ':');
        all_file.push_back(
            std::make_pair(line_split[0], std::stoi(line_split[1])));
      }
    }
    file.close();
  }
  // display all_file
  for (size_t i = 0; i < all_file.size(); i += 1) {
    for (size_t j = i + 1; j < all_file.size(); j += 1) {
      if (all_file[i].second < all_file[j].second) {
        std::pair<std::string, int> tmp = all_file[i];
        all_file[i] = all_file[j];
        all_file[j] = tmp;
      }
    }
  }
  return all_file;
}

/**
 * @brief update selection
 *
 */
void arcade::CoreModule::updateSelection()
{
  std::string selection = "";

  // Generate the selection
  std::string username = "\n Enter your username :\n";
  std::string graphic = "\n selected graphic library:\n";
  std::string game = "\n selected game library:\n";
  std::string score = "\n Hight Score of ";

  // Add value to the selection
  username += " " + this->_menuData._username + " \n\n";
  for (size_t i = 0; i < this->_menuData._graphicLibList.size(); i += 1) {
    if (i == this->_menuData.indexGraphic)
      graphic += " -> " + this->_menuData._graphicLibList[i] + " \n";
    else
      graphic += "    " + this->_menuData._graphicLibList[i] + " \n";
  }
  graphic += "\n";
  for (size_t i = 0; i < this->_menuData._gameLibList.size(); i += 1) {
    if (i == this->_menuData.indexGame)
      game += " -> " + this->_menuData._gameLibList[i] + " \n";
    else
      game += "    " + this->_menuData._gameLibList[i] + " \n";
  }
  game += "\n";

  // Focus version
  int max_len = std::max(max_len_line(username),
                         std::max(max_len_line(graphic), max_len_line(game)));
  switch (this->_menuData._type) {
  case arcade::ICoreModule::MenuSelection::USERNAME:
    generateFocusVersion(username, max_len);
    break;
  case arcade::ICoreModule::MenuSelection::GRAPHIC:
    generateFocusVersion(graphic, max_len);
    break;
  case arcade::ICoreModule::MenuSelection::GAME:
    generateFocusVersion(game, max_len);
    break;
  }

  // Add Hight score of the game
  // DLLoader<std::string> loaderTypeModule(
  //     this->_menuData._gameLibList[this->_menuData.indexGame]);
  arcade::CoreModule::_nameLoader.push_back(DLLoader<std::string>(
      this->_menuData._gameLibList[this->_menuData.indexGame]));
  std::string moduleName = _nameLoader.back().getInstance("getName");
  score += moduleName + " :\n";
  std::vector<std::string> split_player_score;
  for (size_t i = 1; i < 6; i += 1) {
    split_player_score.push_back(std::to_string(i) + ".");
  }
  std::vector<std::pair<std::string, int>> all_file =
      getScoreFromFile(moduleName);
  // add score of player
  for (size_t i = 0; i < all_file.size() && i < 5; i += 1) {
    split_player_score[i] = std::to_string(i + 1) + ". " + all_file[i].first +
                            " : " + std::to_string(all_file[i].second);
  }
  for (std::string line : split_player_score) {
    score += line + "\n";
  }

  selection = username + "\n" + graphic + "\n" + game + "\n" + score + "\n" +
              this->_menuData._description;

  this->getGraphicModule()->clearWindow();
  this->getGraphicModule()->drawText(selection, 0, 0, 30);
  this->getGraphicModule()->displayWindow();
}

/**
 * @brief selection loop
 *
 */
void arcade::CoreModule::selectionLoop()
{
  this->updateSelection();
  while (this->_coreStatus == CoreStatus::SELECTION) {
    arcade::KeyboardInput actualKeyPress = this->getGraphicModule()->getInput();
    this->handleKeyEvent(actualKeyPress);
    if (actualKeyPress != arcade::KeyboardInput::NONE)
      this->updateSelection();
  }
}

void arcade::CoreModule::updateRunning()
{
  int game_scale = 30;
  std::pair<char, std::string> sprite;

  std::vector<std::vector<std::pair<int, std::vector<std::pair<int, int>>>>>
      allLayerSpritesCoordinates;
  std::vector<std::pair<int, std::vector<std::pair<int, int>>>>
      allSpritesCoordinates;
  for (int j = 0; j < this->_gameData.entities.size(); j += 1) {
    for (auto &i : this->_gameData.sprite_value) {
      std::vector<std::pair<int, int>> coordinates;
      for (size_t k = 0; k < this->_gameData.entities[j].size(); k += 1) {
        if (this->_gameData.entities[j][k].sprite == i.first)
          coordinates.push_back(std::make_pair(
              this->_gameData.entities[j][k].position.first,
              this->_gameData.entities[j][k].position.second + 30));
      }
      allSpritesCoordinates.push_back(std::make_pair(i.first, coordinates));
    }
    allLayerSpritesCoordinates.push_back(allSpritesCoordinates);
  }

  this->getGameModule()->updateGame();
  this->getGraphicModule()->clearWindow();
  this->getGraphicModule()->drawText(
      "Graphic:" + this->getGraphicModule()->getName() +
          " | Game:" + this->getGameModule()->getName() +
          " | Score: " + std::to_string(this->getGameData().score),
      0,
      0,
      game_scale);
  // draw sprites on map
  for (size_t i = 0; i < this->getGameData().entities.size(); i += 1) {
    for (size_t j = 0; j < allLayerSpritesCoordinates[i].size(); j += 1) {
      sprite.first = allLayerSpritesCoordinates[i][j].first;
      sprite.second = this->getGameData()
                          .sprite_value[allLayerSpritesCoordinates[i][j].first];
      this->getGraphicModule()->drawAllSprite(
          sprite,
          allLayerSpritesCoordinates[i][j].second,
          game_scale,
          game_scale);
    }
  }
  this->getGraphicModule()->drawText(
      this->_gameData._description,
      0,
      this->getGameData().entities[0].back().position.second + (2 * 30),
      game_scale);
  this->getGraphicModule()->displayWindow();
}

static void addScoreInFile(std::string path, int score, std::string username)
{
  std::ofstream file;
  file.open(path, std::ios::app);
  std::string str = username + ":" + std::to_string(score) + "\n";
  file << str;
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
    this->updateTimers();
    this->updateRunning();
    input = this->getGraphicModule()->getInput();
    this->handleKeyEvent(input);
    this->getGameModule()->handdleKeyEvents(input);
  }
  if (this->getGameModule()->getGameStatus() ==
      arcade::IGameModule::GameStatus::WIN) {
    this->_gameData.score += 1000;
    addScoreInFile("scoreArcade/" + this->getGameModule()->getName() + ".txt",
                   this->_gameData.score,
                   this->_menuData._username);
  } else if (this->getGameModule()->getGameStatus() ==
             arcade::IGameModule::GameStatus::GAMEOVER) {
    addScoreInFile("scoreArcade/" + this->getGameModule()->getName() + ".txt",
                   this->_gameData.score,
                   this->_menuData._username);
  }
}

/**
 * @brief update the timer
 *
 */
void arcade::CoreModule::updateTimers()
{
  for (int i = 0; i < this->_timers.size(); i += 1) {
    this->_timers[i].end = std::chrono::steady_clock::now();
    this->_timers[i].duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            this->_timers[i].end - this->_timers[i].start);
  }
}

/**
 * @brief reset the timer
 *
 */
void arcade::CoreModule::resetTimers(int index)
{
  if (index >= this->_timers.size())
    throw std::exception();
  this->_timers[index].start = std::chrono::steady_clock::now();
}

/**
 * @brief get the timer
 *
 * @return arcade::AGameModule::timer
 */
std::vector<arcade::ICoreModule::timer> arcade::CoreModule::getTimers() const
{
  return this->_timers;
}