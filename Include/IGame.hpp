/*
** IGame.hpp for arcade in /home/aubanel_m/tek2/arcade/Games/Snake
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Thu Mar 09 13:54:29 2017 aubanel_m
** Last update Sun Apr  9 12:55:37 2017 Aubanel Maxime
*/

#ifndef _IGAME_HPP_
# define _IGAME_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include "IGUI.hpp"
#include <fstream>

class IGame
{
public:
  virtual void            Init_Core_Game() = 0;
  virtual void            DISPLAY(IGUI *GUI) = 0;
  virtual int             CYCLE(Game::Command) = 0;
  virtual Game::s_game*   GET_core_game() const = 0;
  virtual Game::s_board_info*     GET_Board_info() = 0;
  virtual void            RESTART() = 0;

public:
  virtual                 ~IGame() {}
};

#endif
