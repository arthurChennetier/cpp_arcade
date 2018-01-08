/*
** Ncurses.hpp for arcade in /home/aubanel_m/tek2/cpp_arcade/arcade/GUIs
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Thu Mar 09 21:14:13 2017 aubanel_m
** Last update Sun Apr  9 18:44:57 2017 Aubanel Maxime
*/

#ifndef _NCURSES_HPP_
# define _NCURSES_HPP_

#include "IGUI.hpp"
#include <ncurses.h>
#include <curses.h>
#include <menu.h>

class Ncurses : public IGUI
{
private:
  WINDOW    *WIN;
  WINDOW    *BOARD;
  WINDOW    *SCORE;

private:
  int       _y;
  int       _x;

private:
  int       _SCORE;

private:
  Game::Command _DIR;

public:
  void        Init_GUI();
  void        Init_Game(int, int);
  void        DISPLAY_Score(int);
  void        Keyboard();
  std::string Launcher(std::vector<t_directory>);
  void        Launcher_Header();
  void        Clear_WIN();
  void        DISPLAY_Level(int);
  void        DISPLAY_background(std::string&);

public:
  void        Dead_Ghost(int, int);
  void        Ghost(int, int, int);
  void        Space(int, int);
  void        B_Block(int, int);
  void        S_Circle(int, int);
  void        B_Circle(int, int, Game::Command);
  void        S_Dot(int, int);
  void 		    B_Dot(int, int);
  void        Refresh();
  void        B_Circle_Yellow(int, int, Game::Command);
  void        S_Star(int, int);

public:
  Game::Command GET_key();

public:
  Ncurses();
  virtual ~Ncurses();
};

extern "C" Ncurses* C_LIB();

#endif
