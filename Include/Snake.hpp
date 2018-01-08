/*
** Snake.hpp for arcade in /home/aubanel_m/tek2/arcade/Games/Snake
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Thu Mar 09 13:55:23 2017 aubanel_m
** Last update Sun Apr  9 12:53:22 2017 Aubanel Maxime
*/

#ifndef _SNAKE_HPP_
# define _SNAKE_HPP_

#include "IGame.hpp"

typedef struct s_node
{
  int          x;
  int          y;
} t_node;

class Snake : public IGame
{
////////GENERAL VARIABLE///////
private:
  int       TIME;
  int       _SCORE;
  int       _SPEED;
  bool      _PAUSE;
  int       _LVL;

////////GAME VARIABLE///////////
private:
  int**       _Board;
  int         _y;
  int         _x;
  Game::Command         _DIR;
  std::vector<t_node> BODY;

////////HEAD OF SNAKE////////
private:
  int         _HEAD_X;
  int         _HEAD_Y;
  int         _HEAD_XOLD;
  int         _HEAD_YOLD;

//////KEYBOARD////////
private:
  char        _KEY;

/////IGAME FONCTION//////
public:
  void      Init_Core_Game(); //
  void      DISPLAY(IGUI *GUI);
  int       CYCLE(Game::Command); //
  Game::s_game*   GET_core_game() const; //
  Game::s_board_info*     GET_Board_info();

/////FUNCTION/////
public:
  void 		setDir(Game::Command DIR);
  Game::Command getDir();
  void		get_map(); //
  void		where_am_i();
  int       Check_Key(Game::Command dir);
  void      Init_Map(int, int); //
  void      Init_Data(); //
  void      GO_up(); //
  void      GO_down(); //
  void      GO_left(); //
  void      GO_right(); //
  int       CHECK(); //
  void      LevelUp();
  void      MAJ_Node(); //
  void      SPAWN_Fruit(); //
  void      ADD_Node(); //
  void      DISPLAY_Board(IGUI *GUI);
  void      DISPLAY_Score(IGUI *GUI);
  void      Boost();
  void      RESTART();



 public:
  Snake();
  virtual ~Snake();
};
////MOULINETTE////

extern "C" void Play();

extern "C" Snake* C_GAME();

#endif
