/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** main
*/

#include <Arcade.hpp>
#include <CoreModule.hpp>
#include <iostream>
#include <unistd.h>
#include "Shell.hpp"

/**
 * @brief check if the library is a good graphic library
 *
 * @param path_graphic_lib path of the graphic library
 * @return true if the library is a good graphic library
 * @return false if the library is not a good graphic library
 */
bool is_good_graphic_lib(char *path_graphic_lib)
{
  if (access(path_graphic_lib, F_OK) == ERROR)
    return false;
  char *lib_name = basename(path_graphic_lib);
  if (strncmp(lib_name, "arcade_", 7) != OK)
    return false;
  if (strncmp(&(lib_name[strlen(lib_name) - 3]), ".so", 3) != OK)
    return false;
  arcade::CoreModule::DLLoader<arcade::ModuleType> loader(path_graphic_lib);
  arcade::ModuleType graphicModule = loader.getInstance("getType");
  if (graphicModule != arcade::ModuleType::GRAPHIC)
    return false;
  return true;
}

/**
 * @brief display the help
 *
 */
void help(void)
{
  std::cout << "USAGE :" << std::endl;
  std::cout << "\t./arcade graphic_lib_path" << std::endl;
}

int main(int ac, char **av)
{
  if (ac != 2) {
    help();
    return KO;
  }
  if (is_good_graphic_lib(av[1]) == false) {
    std::cerr << "Error: The graphic library is not found" << std::endl;
    return KO;
  }
  Shell shell;
  shell.run(av[1]);
  return OK;
}
