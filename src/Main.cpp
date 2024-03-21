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

int is_good_graphic_lib(char *path_graphic_lib)
{
  if (access(path_graphic_lib, F_OK) == -1)
    return -1;
  char *lib_name = basename(path_graphic_lib);
  DLLoader<arcade::IModule> loader(path_graphic_lib);
  if (strncmp(lib_name, "arcade_", 7) != 0)
    return -1;
  if (strncmp(&(lib_name[strlen(lib_name) - 3]), ".so", 3) != 0)
    return -1;
  return 0;
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
    return 84;
  }
  if (is_good_graphic_lib(av[1]) == -1) {
    std::cerr << "Error: The graphic library is not found" << std::endl;
    return 84;
  }
  return 0;
}
