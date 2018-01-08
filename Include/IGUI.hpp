/*
** IGUI.hpp for arcade in /home/aubanel_m/tek2/cpp_arcade/arcade/GUIs
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Thu Mar 09 21:09:23 2017 aubanel_m
** Last update Sun Apr  9 18:40:46 2017 Aubanel Maxime
*/


#ifndef _IGUI_HPP_
# define _IGUI_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "launcher.hpp"
#include "Protocol.hpp"

class IGUI
{
public:
  virtual void              Init_GUI() = 0;
  virtual void              Init_Game(int, int) = 0;
  virtual std::string       Launcher(std::vector<t_directory>) = 0;
  virtual void              DISPLAY_background(std::string&) = 0;
  virtual void              Keyboard() = 0;
  virtual void              Clear_WIN() = 0;
  virtual void              DISPLAY_Score(int) = 0;
  virtual void              DISPLAY_Level(int) = 0;

public:
  virtual void 		          Dead_Ghost(int, int) = 0;
  virtual void 		          Ghost(int, int, int) = 0;
  virtual void              Space(int, int) = 0;
  virtual void              B_Block(int, int) = 0;
  virtual void              S_Circle(int, int) = 0;
  virtual void              B_Circle(int, int, Game::Command) = 0;
  virtual void              S_Dot(int, int) = 0;
  virtual void              Refresh() = 0;
  virtual void              B_Circle_Yellow(int, int, Game::Command) = 0;
  virtual void              S_Star(int, int) = 0;
  virtual void			        B_Dot(int, int) = 0;

public:
  virtual Game::Command     GET_key() = 0;

public:
  virtual                   ~IGUI() {};
};

#endif
