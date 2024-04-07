/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#ifndef COREMODULE_HPP_
#define COREMODULE_HPP_

#include <Arcade.hpp>
#include <arcade/ICoreModule.hpp>
#include <dlfcn.h>
#include <iostream>
#include <memory>
#include <vector>

namespace arcade {
class CoreModule : virtual public ICoreModule {
public:
  CoreModule();
  ~CoreModule();

  void setCoreStatus(CoreStatus status);
  CoreStatus getCoreStatus() const;

  arcade::IDisplayModule *getGraphicModule();
  arcade::IGameModule *getGameModule();

  void setGraphicModule(std::unique_ptr<arcade::IDisplayModule> module);
  void setGameModule(std::unique_ptr<arcade::IGameModule> module);

  void getLib(std::string pathLib);
  void loadLib(std::string pathLib);
  void addLibList(std::string pathLib);
  void generateScore();

  void handleKeyEvent(arcade::KeyboardInput key);
  void launchSelection();
  void addCharUsername(char c);
  void handleKeySelection(arcade::KeyboardInput key);
  void handleKeyRunning(arcade::KeyboardInput key);

  arcade::ICoreModule::MenuData getMenuData() const;

  void setGameData(arcade::GameData gameData);
  arcade::GameData getGameData() const;

  int coreLoop();
  void runningLoop();
  void updateRunning();
  void selectionLoop();
  void updateSelection();

  void updateTimers();
  void resetTimers(int index);
  std::vector<arcade::ICoreModule::timer> getTimers() const;

  template <typename T>
  class DLLoader {
  public:
    void *handle;

    // template <typename T>
    DLLoader(const std::string &libPath)
    {
      handle = dlopen(libPath.c_str(), RTLD_GLOBAL | RTLD_LAZY);
      if (!handle) {
        std::cerr << dlerror() << std::endl;
        exit(1);
      }
    };

    ~DLLoader(){};

    T getInstance(const std::string &funcName)
    {
      void *sym = dlsym(handle, funcName.c_str());
      if (!sym) {
        std::cerr << dlerror() << std::endl;
        exit(1);
      }
      return reinterpret_cast<T (*)()>(sym)();
    };

    void DLLunloader()
    {
      if (handle) {
        dlclose(handle);
      }
    };
  };
  std::vector<DLLoader<std::string>> _nameLoader;
  std::vector<DLLoader<arcade::ModuleType>> _libList;
  std::vector<std::pair<DLLoader<std::unique_ptr<arcade::IDisplayModule>>,
                        DLLoader<std::unique_ptr<arcade::IGameModule>>>>
      _interfaceList;
};
}; // namespace arcade

#endif /* !COREMODULE_HPP_ */
