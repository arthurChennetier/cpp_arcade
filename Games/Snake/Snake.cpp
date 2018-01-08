/*
** Snake.cpp for arcade in /home/aubanel_m/tek2/arcade/Games/Snake
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Thu Mar 09 13:54:07 2017 aubanel_m
** Last update Sun Apr  9 22:18:41 2017 Aubanel Maxime
*/

#include "../../Include/Snake.hpp"

void      Snake::GO_up()
{
  if (_DIR == Game::Command::DOWN)
    return ;
  _DIR = Game::Command::UP;
}

void      Snake::GO_down()
{
  if (_DIR == Game::Command::UP)
    return ;
  _DIR = Game::Command::DOWN;
}

void      Snake::GO_right()
{
  if (_DIR == Game::Command::LEFT)
    return ;
  _DIR = Game::Command::RIGHT;
}

void      Snake::GO_left()
{
  if (_DIR == Game::Command::RIGHT)
    return ;
  _DIR = Game::Command::LEFT;
}

int       Snake::CHECK()
{
  if (_HEAD_X <= 0 && _DIR == Game::Command::LEFT)
    return (-1);
  else if (_HEAD_X == _x - 1 && _DIR == Game::Command::RIGHT)
    return (-1);
  else if (_HEAD_Y <= 0 && _DIR == Game::Command::UP)
    return (-1);
  else if (_HEAD_Y == _y - 1 && _DIR == Game::Command::DOWN)
    return (-1);
  return (0);
}

void      Snake::DISPLAY_Score(IGUI *GUI)
{
  GUI->DISPLAY_Score(_SCORE);
  GUI->DISPLAY_Level(_LVL);
}

void      Snake::DISPLAY(IGUI *GUI)
{
  std::string	path("test");

  GUI->DISPLAY_background(path);
  DISPLAY_Score(GUI);
  DISPLAY_Board(GUI);
  GUI->Refresh();
}

void      Snake::LevelUp()
{
  _LVL = _LVL + 1;
  _SPEED = _SPEED - 5000;
}

void      Snake::DISPLAY_Board(IGUI *GUI)
{
  for (int i = 0; i < _y; i++) {
    for (int k = 0; k < _x; k++) {
      {
        if (_Board[i][k] == 0)
          GUI->Space(i + 1, k + 1);
        if (_Board[i][k] == 3)
          GUI->B_Circle(i + 1, k + 1, _DIR);
        if (_Board[i][k] == 1)
          GUI->S_Circle(i + 1, k + 1);
        if (_Board[i][k] == 2)
          GUI->S_Star(i + 1, k + 1);
      }
    }
  }
}

void      Snake::SPAWN_Fruit()
{
  int     x = rand() % _x;
  int     y = rand() % _y;

  if (_Board[y][x] == 0)
    _Board[y][x] = 2;
  else
    SPAWN_Fruit();
}

void      Snake::MAJ_Node()
{
  int     x;
  int     y;

  if (BODY.size() == 0)
    return ;
  for (std::vector<t_node>::iterator it = BODY.begin(); it != BODY.end(); ++it)
    {
      y = it->y;
      x = it->x;
      _Board[it->y][it->x] = 0;
      it->x = _HEAD_XOLD;
      it->y = _HEAD_YOLD;
      _Board[it->y][it->x] = 1;
      _HEAD_YOLD = y;
      _HEAD_XOLD = x;
    }
}

Game::s_board_info* Snake::GET_Board_info()
{
  Game::s_board_info    *info = new Game::s_board_info;

  info->height = _y;
  info->width = _x;
  return (info);
}

int          Snake::Check_Key(Game::Command dir)
{
  if (dir == Game::Command::ESCAPE
   || dir == Game::Command::NEXTLIB
   || dir == Game::Command::PREVLIB
   || dir == Game::Command::NEXTGAME
   || dir == Game::Command::PAUSE
   || dir == Game::Command::RESTART)
    {
      return (-1);
    }
  return (0);
}

int          Snake::CYCLE(Game::Command new_DIR)
{
  if (Check_Key(new_DIR) != 0)
    return ((int)new_DIR);
  if (new_DIR == Game::Command::UP)
    GO_up();
  else if (new_DIR == Game::Command::DOWN)
    GO_down();
  else if (new_DIR == Game::Command::LEFT)
    GO_left();
  else if (new_DIR == Game::Command::RIGHT)
    GO_right();
  TIME += 1;
  if (CHECK() == -1)
    return (-1);
  _HEAD_XOLD = _HEAD_X;
  _HEAD_YOLD = _HEAD_Y;
  _Board[_HEAD_Y][_HEAD_X] = 0;
  MAJ_Node();
  if (_DIR == Game::Command::UP)
    _HEAD_Y -= 1;
  else if (_DIR == Game::Command::DOWN)
    _HEAD_Y += 1;
  else if (_DIR == Game::Command::LEFT)
    _HEAD_X -= 1;
  else if (_DIR == Game::Command::RIGHT)
    _HEAD_X += 1;
  if (_Board[_HEAD_Y][_HEAD_X] == 1)
    return (-1);
  if (_Board[_HEAD_Y][_HEAD_X] == 2)
    ADD_Node();
  _Board[_HEAD_Y][_HEAD_X] = 3;
  return (0);
}

void      Snake::ADD_Node()
{
  t_node *_new = new t_node;

  _new->x = _HEAD_XOLD;
  _new->y = _HEAD_YOLD;
  BODY.push_back(*_new);
  _SCORE = _SCORE + 1;
  if (_SCORE > 3)
    SPAWN_Fruit();
  if (_SCORE % 2 == 0 && _LVL <= 17)
    LevelUp();
}

void          Snake::Init_Map(int y, int x)
{
  _y = y;
  _x = x;
  _Board = new int*[y];
  for (int i = 0; i < y; i++) {
    _Board[i] = new int[x];
    for (int k = 0; k < x; k++) {
      _Board[i][k] = 0;
    }
  }
}

void          Snake::Init_Data()
{
  srand((unsigned int)time(NULL));
  _LVL = 0;
  TIME = 0;
  _HEAD_X = _x / 2;
  _HEAD_Y = _y / 2;
  _DIR = Game::Command::UP;
  BODY.clear();
  _SPEED = 100000;
  _SCORE = 0;
}

void          Snake::Init_Core_Game()
{
  Init_Map(_y, _x);
  Init_Data();
  CYCLE(Game::Command::UP);
  ADD_Node();
  CYCLE(Game::Command::UP);
  ADD_Node();
  CYCLE(Game::Command::UP);
  ADD_Node();
  SPAWN_Fruit();

}

Game::s_game*         Snake::GET_core_game() const
{
  Game::s_game        *my_t_game = new Game::s_game;

  my_t_game->board = _Board;
  my_t_game->score = _SCORE;
  my_t_game->speed = _SPEED;
  return (my_t_game);
}

void                  Snake::RESTART()
{
  Init_Core_Game();
}

Snake::Snake()
{
  _y = 30;
  _x = 30;
  Init_Core_Game();
}

Snake::~Snake()
{
}

void 		Snake::setDir(Game::Command DIR)
{
  this->_DIR = DIR;
}

Game::Command 	Snake::getDir()
{
  return this-> _DIR;
}

void			Snake::get_map()
{
  int 			height = this->_x;
  int 			width = this->_y;
  size_t 		size =  sizeof(arcade::GetMap)
				+ sizeof(arcade::TileType)
				  * height * width;
  arcade::GetMap	*info = new arcade::GetMap [size];
  int 			i = 0;
  int 			y = 0;
  int 			x;

  info->height = (uint16_t)height;
  info->width = (uint16_t)width;
  info->type = arcade::CommandType::GET_MAP;
  while (y < height)
    {
      x = 0;
      while (x < width)
	{
	  if (this->_Board[y][x] == 0)
	    info->tile[i] = arcade::TileType::EMPTY;
	  else if (this->_Board[y][x] == 2)
	    info->tile[i] = arcade::TileType::POWERUP;
	  else if (this->_Board[y][x] == 3 || this->_Board[y][x] == 1)
	    info->tile[i] = arcade::TileType::EMPTY;
	  x++;
	  i++;
	}
      y++;
    }
  std::cout.write((const char*)info,
		  sizeof(arcade::GetMap) +
		  sizeof(arcade::TileType) * height * width);
  delete (info);
}

void 		Snake::where_am_i()
{
  int 			i = 1;
  unsigned long		lenght = BODY.size() + 1;
  arcade::WhereAmI	*info = new arcade::WhereAmI
  					[sizeof(arcade::WhereAmI)
				       + sizeof(arcade::Position)
					 * lenght];

  info->lenght = (uint16_t )lenght;
  info->type = arcade::CommandType::WHERE_AM_I;
  info->position[0].y = (uint16_t )_HEAD_Y;
  info->position[0].x = (uint16_t )_HEAD_X;
  for (std::vector<t_node>::iterator it = BODY.begin(); it != BODY.end(); ++it)
    {
      info->position[i].y = (uint16_t)it->y;
      info->position[i].x = (uint16_t)it->x;
      i++;
    }
  std::cout.write((const char*)info, sizeof(arcade::WhereAmI)
				     + sizeof(arcade::Position)
				       * lenght);
  delete (info);
}

extern "C" void Play()
{
  Snake		*snake = new Snake();
  arcade::CommandType buf;

  while (std::cin.read((char*)&buf, sizeof(arcade::CommandType)))
    {
      if (buf == arcade::CommandType::GET_MAP)
	snake->get_map();
      else if (buf == arcade::CommandType::WHERE_AM_I)
	snake->where_am_i();
      else if (buf == arcade::CommandType::GO_UP)
	snake->setDir(Game::Command::UP);
      else if (buf == arcade::CommandType::GO_DOWN)
	snake->setDir(Game::Command::DOWN);
      else if (buf == arcade::CommandType::GO_LEFT)
	snake->setDir(Game::Command::LEFT);
      else if (buf == arcade::CommandType::GO_RIGHT)
	snake->setDir(Game::Command::RIGHT);
      else if (buf == arcade::CommandType::PLAY)
	snake->CYCLE(snake->getDir());
    }
}

extern "C" Snake* C_GAME()
{
  return (new Snake());
}
