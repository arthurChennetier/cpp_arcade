/*
** Snake.cpp for arcade in /home/aubanel_m/tek2/arcade/Games/Snake
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Thu Mar 09 13:54:07 2017 aubanel_m
** Last update Sun Apr  9 22:18:57 2017 Aubanel Maxime
*/

#include <iosfwd>
#include "../../Include/Pacman.hpp"

void      Pacman::DISPLAY_Score(IGUI *GUI)
{
  GUI->DISPLAY_Score(_SCORE);
  GUI->DISPLAY_Level(_LVL);
}

void      Pacman::DISPLAY(IGUI *GUI)
{
  std::string	path("pac");

  GUI->DISPLAY_background(path);
  DISPLAY_Board(GUI);
  DISPLAY_Score(GUI);
  GUI->Refresh();
}

void      Pacman::RESTART()
{
  Init_Core_Game();
}

void      Pacman::DISPLAY_Board(IGUI *GUI)
{
  for (int i = 0; i < _y; i++) {
    for (int k = 0; k < _x; k++) {
        if (_Board[i][k] == 0)
          GUI->Space(i + 1, k + 1);
        if (_Board[i][k] == 3)
          GUI->B_Circle_Yellow(i + 1, k + 1, _DIR);
        if (_Board[i][k] == 2)
          GUI->B_Block(i + 1, k + 1);
        if (_Board[i][k] == 4)
          GUI->S_Dot(i + 1, k + 1);
        if (_Board[i][k] == 5)
          GUI->Space(i + 1, k + 1);
	if (_Board[i][k] == 7)
	  GUI->B_Dot(i + 1, k + 1);
	if (_Board[i][k] > 10)
	  {
	    if (bonus == 0)
	      GUI->Ghost(i + 1, k + 1, _Board[i][k]);
	    else
	      GUI->Dead_Ghost(i + 1, k + 1);
	  }
      }
    }
}

int          Pacman::Check_Key(Game::Command dir)
{
  if (dir == Game::Command::ESCAPE
   || dir == Game::Command::PREVLIB
   || dir == Game::Command::NEXTLIB
   || dir == Game::Command::NEXTGAME
   || dir == Game::Command::PAUSE
   || dir == Game::Command::RESTART)
    {
      return (-1);
    }
  return (0);
}

int       Pacman::CHECK()
{
  if (_HEAD_X <= 0 && _DIR == Game::Command::LEFT)
    return (-1);
  else if (_HEAD_X == _x - 1 && _DIR == Game::Command::RIGHT)
    return (-1);
  else if (_HEAD_Y <= 0 && _DIR == Game::Command::UP)
    return (-1);
  else if (_HEAD_Y == _y - 1 && _DIR == Game::Command::DOWN)
    return (-1);
  else if (_DIR == Game::Command::LEFT && _Board[_HEAD_Y][_HEAD_X - 1] == 2)
    return (-1);
  else if (_DIR == Game::Command::RIGHT && _Board[_HEAD_Y][_HEAD_X + 1] == 2)
    return (-1);
  else if (_DIR == Game::Command::UP && _Board[_HEAD_Y - 1][_HEAD_X] == 2)
    return (-1);
  else if (_DIR == Game::Command::DOWN && _Board[_HEAD_Y + 1][_HEAD_X] == 2)
    return (-1);
  return (0);
}

int          Pacman::CHECK2(Game::Command dir)
{
  if (_HEAD_X <= 0 && _DIR == Game::Command::LEFT)
    return (-1);
  else if (_HEAD_X == _x - 1 && _DIR == Game::Command::RIGHT)
    return (-1);
  else if (_HEAD_Y <= 0 && _DIR == Game::Command::UP)
    return (-1);
  else if (_HEAD_Y == _y - 1 && _DIR == Game::Command::DOWN)
    return (-1);
  else if (dir == Game::Command::UP && _Board[_HEAD_Y - 1][_HEAD_X] == 2)
    return (-1);
  else if (dir == Game::Command::DOWN && _Board[_HEAD_Y + 1][_HEAD_X] == 2)
    return (-1);
  else if (dir == Game::Command::RIGHT && _Board[_HEAD_Y][_HEAD_X + 1] == 2)
    return (-1);
  else if (dir == Game::Command::LEFT && _Board[_HEAD_Y][_HEAD_X - 1] == 2)
    return (-1);
  return (0);
}

int          Pacman::CHECK3()
{
  if (save_DIR == Game::Command::UP && _Board[_HEAD_Y - 1][_HEAD_X] != 2)
    return (0);
  else if (save_DIR == Game::Command::DOWN && _Board[_HEAD_Y + 1][_HEAD_X] != 2)
    return (0);
  else if (save_DIR == Game::Command::LEFT && _Board[_HEAD_Y][_HEAD_X - 1] != 2)
    return (0);
  else if (save_DIR == Game::Command::RIGHT && _Board[_HEAD_Y][_HEAD_X + 1] != 2)
    return (0);
  return (-1);
}

int          Pacman::CYCLE(Game::Command new_DIR)
{
  if (check_end() == 1)
    LevelUp();
  if (Check_Key(new_DIR) != 0)
    return ((int)new_DIR);
  if (GHOST_move() == -1)
    return (-1);
  if (CHECK2(new_DIR) == -1)
    {
      save_DIR = new_DIR;
      new_DIR = Game::Command::NONE;
    }
  if (CHECK3() == 0)
    {
      _DIR = save_DIR;
      save_DIR = Game::Command::NONE;
    }
  if (new_DIR != Game::Command::NONE)
    _DIR = new_DIR;
  if (CHECK() == -1)
    return (0);
  TIME += 1;
  _Board[_HEAD_Y][_HEAD_X] = _save;
  if (_Board[_HEAD_Y][_HEAD_X] != 5)
    _Board[_HEAD_Y][_HEAD_X] = 0;
  if (_DIR == Game::Command::UP)
    _HEAD_Y -= 1;
  else if (_DIR == Game::Command::DOWN)
    {
      if (is_in_box(_HEAD_X, _HEAD_Y + 1) == -1)
      	_HEAD_Y += 1;
    }
  else if (_DIR == Game::Command::LEFT)
    _HEAD_X -= 1;
  else if (_DIR == Game::Command::RIGHT)
    _HEAD_X += 1;
  if (_Board[_HEAD_Y][_HEAD_X] == 5)
    GO_TP(_HEAD_Y, _HEAD_X);
  if (_Board[_HEAD_Y][_HEAD_X] == 4 || _Board[_HEAD_Y][_HEAD_X] == 7)
    EAT();
  if (bonus > 0)
    bonus++;
  if (bonus >= 50)
    bonus = 0;
  _save = _Board[_HEAD_Y][_HEAD_X];
  _Board[_HEAD_Y][_HEAD_X] = 3;
  return (0);
}

void          Pacman::EAT()
{
  if (_Board[_HEAD_Y][_HEAD_X] == 7)
    {
      _SCORE = _SCORE + 10;
      bonus = 1;
    }
  else
    this->_SCORE++;

}

int           random_TP(std::vector<t_node> vector, int y, int x)
{
  int random = (int)(rand() % vector.size());

  if (vector[random].x != x || vector[random].y != y)
    return (random);
  return (random_TP(vector, y, x));
}

void          Pacman::GO_TP(int y, int x)
{
  int         random;
  t_node      node;

  if (_teleport.size() == 0)
    return ;
  random = random_TP(_teleport, y, x);
  if (random == -1)
    return ;
  node = _teleport[random];
  _HEAD_Y = node.y;
  _HEAD_X = node.x;
}

void          Pacman::add_TP(int y, int x)
{
  t_node *_new = new t_node;

  _new->x = x;
  _new->y = y;
  _teleport.push_back(*_new);
}

void          Pacman::Init_Map(std::string path)
{
  std::string line;
  std::ifstream    file(path);
  int               i;

  if (file)
    {
      std::getline(file, line);
      _y = std::stoi(line);
      std::getline(file, line);
      _x = std::stoi(line);
      _Board = new int*[_y];
      for (i = 0; i < _y; i++) {
        _Board[i] = new int[_x];
      }
      i = 0;
      while (std::getline(file, line))
        {
          for (int k = 0; k < _x; k++) {
            if (line[k] == ' ')
	      {
		if (is_in_box(k, i) == -1)
		  _Board[i][k] = 4;
		else
		  _Board[i][k] = 0;
	      }
            else if (line[k] == 'X')
              _Board[i][k] = 2;
            else if (line[k] == '.')
	      {
		if (is_in_box(k, i) == -1)
		  _Board[i][k] = 4;
		else
		  _Board[i][k] = 0;
	      }
	    else if (line[k] == 'B')
	      _Board[i][k] = 7;
            else if (line[k] == '_')
              _Board[i][k] = 8;
            else if (line[k] == 'T')
              {
                _Board[i][k] = 5;
                add_TP(i, k);
              }
            else if (line[k] == 'P')
              {
                _Board[i][k] = 3;
                _HEAD_Y = i;
                _HEAD_X = k;
              }
            else if (line[k] >= 48 && line[k] <= 57)
              {
                add_ghost(i, k, line[k] - 48);
                _Board[i][k] = 10 + line[k] - 48;
	      }
          }
          i = i + 1;
        }
    }
}

int 		Pacman::ghost_check_up(std::vector<t_ghost>::iterator it)
{
  if (it->y - 1 < 0)
    return (-1);
  if (_Board[it->y - 1][it->x] == 2 || _Board[it->y - 1][it->x] > 10)
    return (-1);
  return (1);
}

int 		Pacman::ghost_check_down(std::vector<t_ghost>::iterator it)
{
  if (it->y + 1 >= _y)
    return (-1);
  if (is_in_box(it->x, it->y) == -1 && is_in_box(it->x, it->y + 1) == 1)
    return (-1);
  if (_Board[it->y + 1][it->x] == 2 || _Board[it->y + 1][it->x] > 10)
    return (-1);
  return (1);
}

int 		Pacman::ghost_check_right(std::vector<t_ghost>::iterator it)
{
  if (it->x + 1 >= _x)
    return (-1);
  if (_Board[it->y][it->x + 1] == 2 || _Board[it->y][it->x + 1] > 10)
    return (-1);
  return (1);
}

int 		Pacman::ghost_check_left(std::vector<t_ghost>::iterator it)
{
  if (it->x - 1 < 0)
    return (-1);
  if (_Board[it->y][it->x - 1] == 2 || _Board[it->y][it->x - 1] > 10)
    return (-1);
  return (1);
}

std::vector<t_ghost>::iterator	Pacman::move_right(std::vector<t_ghost>::iterator it)
{
  int 		type = _Board[it->y][it->x];

  if (it->had_powerup == 4 && is_in_box(it->x, it->y) == -1)
    _Board[it->y][it->x] = 4;
  else if (it->had_powerup == 7 && is_in_box(it->x, it->y) == -1)
    _Board[it->y][it->x] = 7;
  else if (it->had_tp == 1)
    _Board[it->y][it->x] = 5;
  else
  _Board[it->y][it->x] = 0;
  it->x = it->x + 1;
  if (_Board[it->y][it->x] == 4)
    it->had_powerup = 4;
  else if (_Board[it->y][it->x] == 7)
    it->had_powerup = 7;
  else
    it->had_powerup = 0;
  if (_Board[it->y][it->x] == 5)
    it->had_tp = 1;
  else
    it->had_tp = 0;
  _Board[it->y][it->x] = type;
  it->_DIR = Game::Command::RIGHT;
  return it;
}

std::vector<t_ghost>::iterator	Pacman::move_left(std::vector<t_ghost>::iterator it)
{
  int 		type = _Board[it->y][it->x];

  if (it->had_powerup == 4 && is_in_box(it->x, it->y) == -1)
    _Board[it->y][it->x] = 4;
  else if (it->had_powerup == 7 && is_in_box(it->x, it->y) == -1)
    _Board[it->y][it->x] = 7;
  else if (it->had_tp == 1)
    _Board[it->y][it->x] = 5;
  else
    _Board[it->y][it->x] = 0;
  it->x = it->x - 1;
  if (_Board[it->y][it->x] == 4)
    it->had_powerup = 4;
  else if (_Board[it->y][it->x] == 7)
    it->had_powerup = 7;
  else
    it->had_powerup = 0;
  if (_Board[it->y][it->x] == 5)
    it->had_tp = 1;
  else
    it->had_tp = 0;
  _Board[it->y][it->x] = type;
  it->_DIR = Game::Command::LEFT;
  return it;
}

std::vector<t_ghost>::iterator	Pacman::move_up(std::vector<t_ghost>::iterator it)
{
  int 		type = _Board[it->y][it->x];

  if (it->had_powerup == 4 && is_in_box(it->x, it->y) == -1)
    _Board[it->y][it->x] = 4;
  else if (it->had_powerup == 7 && is_in_box(it->x, it->y) == -1)
    _Board[it->y][it->x] = 7;
  else if (it->had_tp == 1)
    _Board[it->y][it->x] = 5;
  else
    _Board[it->y][it->x] = 0;
  it->y = it->y - 1;
  if (_Board[it->y][it->x] == 4)
    it->had_powerup = 4;
  else if (_Board[it->y][it->x] == 7)
    it->had_powerup = 7;
  else
    it->had_powerup = 0;
  if (_Board[it->y][it->x] == 5)
    it->had_tp = 1;
  else
    it->had_tp = 0;
  _Board[it->y][it->x] = type;
  it->_DIR = Game::Command::UP;
  return it;
}

std::vector<t_ghost>::iterator	Pacman::move_down(std::vector<t_ghost>::iterator it)
{
  int 		type = _Board[it->y][it->x];

  if (it->had_powerup == 4 && is_in_box(it->x, it->y) == -1)
    _Board[it->y][it->x] = 4;
  else if (it->had_powerup == 7 && is_in_box(it->x, it->y) == -1)
    _Board[it->y][it->x] = 7;
  else if (it->had_tp == 1)
    _Board[it->y][it->x] = 5;
  else
    _Board[it->y][it->x] = 0;
  it->y = it->y + 1;
  if (_Board[it->y][it->x] == 4)
    it->had_powerup = 4;
  else if (_Board[it->y][it->x] == 7)
    it->had_powerup = 7;
  else
    it->had_powerup = 0;
  if (_Board[it->y][it->x] == 5)
    it->had_tp = 1;
  else
    it->had_tp = 0;
  _Board[it->y][it->x] = type;
  it->_DIR = Game::Command::DOWN;
  return it;
}

std::vector<t_ghost>::iterator	Pacman::random_move(std::vector<t_ghost>::iterator it)
{
  int 		indic = rand() % 4;
  int 		test = 0;

  while (indic < 5)
    {
      if (indic == 0 && it->_DIR != Game::Command::DOWN)
	{
	  if (ghost_check_up(it) == 1)
	    return (move_up(it));
	}
      else if (indic == 1 && it->_DIR != Game::Command::UP)
	{
	  if (ghost_check_down(it) == 1)
	    return (move_down(it));
	}
      else if (indic == 2 && it->_DIR != Game::Command::RIGHT)
	{
	  if (ghost_check_left(it) == 1)
	    return (move_left(it));
	}
      else if (indic == 3 && it->_DIR != Game::Command::LEFT)
	{
	  if (ghost_check_right(it) == 1)
	    return (move_right(it));
	}
      if (test == 20)
	it->_DIR = Game::Command::NONE;
      if (test > 50)
	return it;
      test++;
      indic = rand() % 4;
    }
  return it;
}

int 		Pacman::getDistance(int x, int y)
{
  int 		distance = 0;

  if (_HEAD_X > x)
    distance = distance + (_HEAD_X - x);
  else
    distance = distance + (x - _HEAD_X);
  if (_HEAD_Y > y)
    distance = distance + (_HEAD_Y - y);
  else
    distance = distance + (y - _HEAD_Y);
  return distance;
}

std::vector<t_ghost>::iterator Pacman::follow_pacman(std::vector<t_ghost>::iterator it)
{
  int 		dist_x;
  int 		dist_y;

  dist_x = it->x - _HEAD_X;
  dist_y = it->y - _HEAD_Y;

      if (dist_x < 0 && it->_DIR != Game::Command::LEFT) // Le pacman est a droite du fantome
	{
	  if (ghost_check_right(it) == 1)
	    return (move_right(it));
	}
      if (dist_y < 0 && it->_DIR != Game::Command::UP) // Le pacman est en dessous du fantome
	{
	  if (ghost_check_down(it) == 1)
	    return (move_down(it));
	}
  	if (dist_x > 0 && it->_DIR != Game::Command::RIGHT) // Le pacman est a gauche du fantome
	  {
	    if (ghost_check_left(it) == 1)
	      return (move_left(it));
	  }
  	if (dist_y > 0 && it->_DIR != Game::Command::DOWN) // Le pacman est au dessus du fantome
	  {
	    if (ghost_check_up(it) == 1)
	      return (move_up(it));
	  }
  it = random_move(it);
  return it;
}

int 				Pacman::is_in_box(int x, int y)
{
  if ((x >= 10 && x <= 17) && (y >= 12 && y <= 16))
    return (1);
  return (-1);
}

std::vector<t_ghost>::iterator	Pacman::init_new_pos(std::vector<t_ghost>::iterator it)
{
  int 			x;
  int 			y;

  x = rand() % 6 + 11;
  y = rand() % 3 + 13;
  while (_Board[y][x] != 0)
    {
      x = rand() % 6 + 11;
      y = rand() % 3 + 13;
    }
  it->x = x;
  it->y = y;
  return it;
}

int          Pacman::GHOST_move()
{
  if (bonus == 0)
    {
      for (std::vector<t_ghost>::iterator it = _ghost.begin();
	   it != _ghost.end(); ++it)
	{
	  if (it->x == _HEAD_X && it->y == _HEAD_Y)
	    return (-1);
	  if (getDistance(it->x, it->y) < 10)
	    it = follow_pacman(it);
	  else
	    it = random_move(it);
	  if (it->x == _HEAD_X && it->y == _HEAD_Y)
	    return (-1);
	}
    }
  else
    {
      for (std::vector<t_ghost>::iterator it = _ghost.begin();
	   it != _ghost.end(); ++it)
	{
	  if (it->x == _HEAD_X && it->y == _HEAD_Y)
	    {
	      _Board[_HEAD_Y][_HEAD_X] = 3;
	      it = init_new_pos(it);
	      _Board[it->y][it->x] = it->type;
	    }
	  it = random_move(it);
	  if (it->x == _HEAD_X && it->y == _HEAD_Y)
	    {
	      _Board[_HEAD_Y][_HEAD_X] = 3;
	      it = init_new_pos(it);
	      _Board[it->y][it->x] = it->type;
	    }
	}
    }
  return (0);
}

void                Pacman::add_ghost(int y, int x, int type)
{
  t_ghost *_new = new t_ghost;

  _new->x = x;
  _new->y = y;
  _new->had_powerup = 0;
  _new->had_tp = 0;
  _new->_DIR = Game::Command::NONE;
  if (type == 1)
    {
      _new->name = "BLINKY";
      _new->type = 11;
    }
  else if (type == 2)
    {
      _new->name = "PINKY";
      _new->type = 12;
    }
  else if (type == 3)
    {
      _new->name = "INKY";
      _new->type = 13;
    }
  else if (type == 4)
    {
      _new->name = "CLYDE";
      _new->type = 14;
    }
  _ghost.push_back(*_new);
}

Game::s_board_info* Pacman::GET_Board_info()
{
  Game::s_board_info    *info = new Game::s_board_info;

  info->height = _y;
  info->width = _x;
  return (info);
}

void          Pacman::Init_Data()
{
  srand((unsigned int)time(NULL));
  _LVL = 1;
  _save = 0;
  TIME = 0;
  bonus = 0;
  _teleport.clear();
  _ghost.clear();
  _DIR = Game::Command::LEFT;
  _SPEED = 50000;
  _SCORE = 0;
  save_DIR = Game::Command::NONE;
}

int		Pacman::check_end()
{
  int 		x;
  int 		y = 0;

  while (y < _y)
    {
      x = 0;
      while (x < _x)
	{
	  if (_Board[y][x] == 7 || _Board[y][x] == 4)
	    return (-1);
	  x++;
	}
      y++;
    }
  for (std::vector<t_ghost>::iterator it = _ghost.begin();
       it != _ghost.end(); ++it)
    {
      if (it->had_powerup == 7 || it->had_powerup == 4)
	return (-1);
    }
  return (1);
}

void		Pacman::LevelUp()
{
  char 		buf[100];

  _LVL++;
  if (_LVL == 4)
    exit(0);
  bonus = 0;
  _save = 0;
  _teleport.clear();
  _ghost.clear();
  _DIR = Game::Command::LEFT;
  save_DIR = Game::Command::NONE;
  sprintf(buf, "Games/Pacman/map/lvl%d.map", _LVL);
  std::string path(buf);
  Init_Map(path);
}

void          Pacman::Init_Core_Game()
{
  Init_Data();
  Init_Map("Games/Pacman/map/lvl1.map");
}

Game::s_game*         Pacman::GET_core_game() const
{
  Game::s_game        *my_t_game = new Game::s_game;

  my_t_game->board = _Board;
  my_t_game->score = _SCORE;
  my_t_game->speed = _SPEED;
  return (my_t_game);
}

void 			Pacman::setDir(Game::Command DIR)
{
  this->_DIR = DIR;
}

int		Pacman::getDir()
{
  return this->_DIR;
}

void		Pacman::get_map()
{
  arcade::GetMap	*info;
  int 			height;
  int 			width;
  int 			i;
  int 			x;
  int 			y;

  height = this->_x;
  width = this->_y;
  if ((info = (arcade::GetMap*)malloc(sizeof(arcade::GetMap)
				      + sizeof(arcade::TileType) * height * width)) == NULL)
    exit(84);
  info->height = (uint16_t)height;
  info->width = (uint16_t)width;
  info->type = arcade::CommandType::GET_MAP;
  i = 0;
  y = 0;
  while (y < height)
    {
      x = 0;
      while (x < width)
	{
	  if (this->_Board[y][x] == 0 || this->_Board[y][x] == 1
	   || this->_Board[y][x] == 4)
	    info->tile[i] = arcade::TileType::EMPTY;
	  else if (this->_Board[y][x] == 5)
	    info->tile[i] = arcade::TileType::OTHER;
	  else if (this->_Board[y][x] == 2)
	    info->tile[i] = arcade::TileType::BLOCK;
	  x++;
	  i++;
	}
      y++;
    }
  std::cout.write((const char*)info,
		  sizeof(arcade::GetMap) +
		  sizeof(arcade::TileType) * height * width);
}

void		Pacman::where_am_i()
{
  arcade::WhereAmI	*info;
  unsigned long		lenght;

  lenght = 1;
  if ((info = (arcade::WhereAmI*)malloc(sizeof(arcade::WhereAmI)
					+ sizeof(arcade::Position)
					  * lenght)) == NULL)
    exit(84);
  info->lenght = (uint16_t )lenght;
  info->type = arcade::CommandType::WHERE_AM_I;
  info->position[0].y = (uint16_t )_HEAD_Y;
  info->position[0].x = (uint16_t )_HEAD_X;
  std::cout.write((const char*)info, sizeof(arcade::WhereAmI)
				     + sizeof(arcade::Position)
				       * lenght);
}

extern "C" void Play()
{
  Pacman	*pacman = new Pacman();
  arcade::CommandType buf;

  while (std::cin.read((char*)&buf, sizeof(arcade::CommandType)))
    {
      if (buf == arcade::CommandType::GET_MAP)
	pacman->get_map();
      else if (buf == arcade::CommandType::WHERE_AM_I)
	pacman->where_am_i();
      else if (buf == arcade::CommandType::GO_UP)
	pacman->setDir(Game::Command::UP);
      else if (buf == arcade::CommandType::GO_DOWN)
	pacman->setDir(Game::Command::DOWN);
      else if (buf == arcade::CommandType::GO_LEFT)
	pacman->setDir(Game::Command::LEFT);
      else if (buf == arcade::CommandType::GO_RIGHT)
	pacman->setDir(Game::Command::RIGHT);
      else if (buf == arcade::CommandType::PLAY)
	pacman->CYCLE((Game::Command )pacman->getDir());
    }
}

Pacman::Pacman()
{
  Init_Core_Game();
}

Pacman::~Pacman()
{

}

extern "C" Pacman* C_GAME()
{
  return (new Pacman());
}
