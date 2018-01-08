/*
** Pacman.hpp for arcade in /home/aubanel_m/tek2/arcade/Games/Pacman
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Thu Mar 09 13:55:23 2017 aubanel_m
** Last update Sun Apr  9 13:18:50 2017 Aubanel Maxime
*/

#ifndef _PACMAN_HPP_
# define _PACMAN_HPP_

#include "IGame.hpp"

typedef struct s_node
{
  int          x;
  int          y;
} t_node;

typedef struct s_ghost
{
  int           x;
  int           y;
  int 		type;
  int 		had_powerup;
  int 		had_tp;
  std::string   name;
  Game::Command _DIR;
} t_ghost;

class Pacman : public IGame
{
////////GENERAL VARIABLE///////
private:
  int       TIME;
  int       _SCORE;
  int       _SPEED;
  bool      _PAUSE;
  int       _LVL;
  int       _save;

////////GAME VARIABLE///////////
private:
  int**       _Board;
  int         _y;
  int         _x;
  int 		bonus;
  Game::Command         _DIR;
  Game::Command        save_DIR;
  std::vector<t_node>  _teleport;
  std::vector<t_ghost> _ghost;

////////HEAD OF Pacman////////
private:
  int         _HEAD_X;
  int         _HEAD_Y;

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
  int 					is_in_box(int x, int y);

  std::vector<t_ghost>::iterator	init_new_pos(std::vector<t_ghost>::iterator it);
  std::vector<t_ghost>::iterator	move_right(std::vector<t_ghost>::iterator it);
  std::vector<t_ghost>::iterator	move_left(std::vector<t_ghost>::iterator it);
  std::vector<t_ghost>::iterator	move_up(std::vector<t_ghost>::iterator it);
  std::vector<t_ghost>::iterator	move_down(std::vector<t_ghost>::iterator it);
  int 		ghost_check_up(std::vector<t_ghost>::iterator it);
  int 		ghost_check_down(std::vector<t_ghost>::iterator it);
  int 		ghost_check_right(std::vector<t_ghost>::iterator it);
  int 		ghost_check_left(std::vector<t_ghost>::iterator it);
  std::vector<t_ghost>::iterator random_move(std::vector<t_ghost>::iterator it);
  std::vector<t_ghost>::iterator follow_pacman(std::vector<t_ghost>::iterator it);
  int 		getDistance(int	x, int y);
  void 		setDir(Game::Command DIR);
  int 		getDir();
  void		get_map();
  void		where_am_i();
  int       Check_Key(Game::Command dir);
  void      add_ghost(int, int, int);
  void      Init_Map(std::string);
  void      Init_Data();
  int       CHECK();
  int       CHECK2(Game::Command);
  int       CHECK3();
  int 		check_end();
  void      LevelUp();
  void      DISPLAY_Board(IGUI *GUI);
  void      DISPLAY_Score(IGUI *GUI);
  void      Boost();
  void      GO_TP(int, int);
  void      add_TP(int, int);
  void      EAT();
  int      GHOST_move();
  void      RESTART();
  

public:
  Pacman();
  virtual ~Pacman();
};

extern "C" Pacman* C_GAME();

#endif
