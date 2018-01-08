/*
** launcher.hpp for cpp_arcade in /home/aubanel_m/tek2/cpp_arcade
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Sat Mar 18 23:42:00 2017 aubanel_m
** Last update Sun Apr  9 01:44:09 2017 Aubanel Maxime
*/

#ifndef _LAUNCHER_HPP_
# define _LAUNCHER_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <dirent.h>

typedef struct s_directory
{
  std::string   name;
  std::string   path;
  std::string   file_name;
}              t_directory;

#endif
