/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** main
*/

#include <iostream>
#include <libgen.h>
#include <unistd.h>

#include <cstring>
#include "DLLoader.hpp"
#include "IModule.hpp"
#include "Macros.hpp"

int is_good_graphic_lib(char *path_graphic_lib)
{
  if (access(path_graphic_lib, F_OK) == ERROR)
    return ERROR;
  char *lib_name = basename(path_graphic_lib);
  DLLoader<arcade::IModule> loader(path_graphic_lib);
  if (strncmp(lib_name, "arcade_", 7) != OK)
    return ERROR;
  if (strncmp(&(lib_name[strlen(lib_name) - 3]), ".so", 3) != OK)
    return ERROR;
  return OK;
}

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
  if (is_good_graphic_lib(av[1]) == ERROR) {
    std::cerr << "Error: The graphic library is not found" << std::endl;
    return KO;
  }
  return OK;
}
