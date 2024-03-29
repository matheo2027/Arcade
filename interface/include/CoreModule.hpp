/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** CoreModule
*/

#ifndef COREMODULE_HPP_
#define COREMODULE_HPP_

#include <arcade/ICoreModule.hpp>
#include <dlfcn.h>
#include <iostream>
#include <memory>
#include <Arcade.hpp>

namespace arcade {
class CoreModule : virtual public ICoreModule{
// class DLLoader {
  // DLLoader(const std::string &libPath)
  // {
  //   handle = dlopen(libPath.c_str(), RTLD_GLOBAL | RTLD_LAZY);
  //   if (!handle) {
  //     std::cerr << dlerror() << std::endl;
  //     exit(1);
  //   }
  // }

  // ~DLLoader()
  // {
  //   if (handle) {
  //     std::cout << "Closing Lib" << std::endl;
  //     dlclose(handle);
  //   }
  // }


// };
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

  void handleKeyEvent(arcade::KeyboardInput key);
  void handleKeySelection(arcade::KeyboardInput key);
  void handleKeyRunning(arcade::KeyboardInput key);

  arcade::MenuData getMenuData() const;

  void setGameData(arcade::GameData gameData);
  arcade::GameData getGameData() const;

  int coreLoop();
  void runningLoop();
  void updateRunning();
  void selectionLoop();
  void updateSelection();

  // template <typename T>
  // class DLLoader {
    // public:
  void *handle;
  template <typename T>
  void DLLoader(const std::string &libPath)
  {
    handle = dlopen(libPath.c_str(), RTLD_GLOBAL | RTLD_LAZY);
    if (!handle) {
      std::cerr << dlerror() << std::endl;
      exit(1);
    }
  }

  template <typename T>
  T getInstance(const std::string &funcName)
  {
    void *sym = dlsym(handle, funcName.c_str());
    if (!sym) {
      std::cerr << dlerror() << std::endl;
      exit(1);
    }
    return reinterpret_cast<T (*)()>(sym)();
  }

  void DLLunloader()
  {
    if (handle) {
      std::cout << "Closing Lib" << std::endl;
      dlclose(handle);
      // return handle;
    }
  }

  // };
};
}; // namespace arcade

#endif /* !COREMODULE_HPP_ */
