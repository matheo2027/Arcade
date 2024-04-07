/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Shell
*/

#include "Shell.hpp"
#include <Arcade.hpp>
#include <CoreModule.hpp>

Shell::Shell()
{
}

Shell::~Shell()
{
}


int Shell::Shell::run(std::string path_graphic_lib)
{
  arcade::CoreModule core;
  core.getLib("./lib/");
  core.loadLib(path_graphic_lib);
  core.generateScore();
  core.coreLoop();
  return OK;
}
