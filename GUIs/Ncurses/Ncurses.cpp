/*
** Ncurses.cpp for arcade in /home/aubanel_m/tek2/cpp_arcade/arcade/GUIs
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Thu Mar 09 21:08:53 2017 aubanel_m
** Last update Sun Apr  9 22:17:31 2017 Aubanel Maxime
*/

#include "../../Include/Ncurses.hpp"

void          Ncurses::Init_Game(int y, int x)
{
  WIN = initscr();
  nodelay(WIN, TRUE);
  start_color();
  use_default_colors();
  noecho();
  curs_set(0);
  init_pair(1, COLOR_WHITE, COLOR_GREEN);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);
  init_pair(5, COLOR_BLACK, COLOR_YELLOW);
  init_pair(11, COLOR_RED, COLOR_RED);
  init_pair(12, COLOR_BLUE, COLOR_BLUE);
  init_pair(13, COLOR_CYAN, COLOR_CYAN);
  init_pair(14, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(15, COLOR_WHITE, COLOR_WHITE);
  _y = y;
  _x = x;
  BOARD = subwin(WIN, _y + 2, _x + 2, (LINES / 2) - (_y / 2), (COLS / 2) - (_x / 2));
  SCORE = subwin(WIN, 5, 17, 2, 30);
  wborder(SCORE, 0, 0, 0, 0, 0, 0, 0, 0);
  wborder(WIN, 0, 0, 0, 0, 0, 0, 0, 0);
  wborder(BOARD, 0, 0, 0, 0, 0, 0, 0, 0);
  wrefresh(WIN);
  wrefresh(BOARD);
}

void          Ncurses::Init_GUI()
{
  WIN = initscr();
  nodelay(WIN, TRUE);
  start_color();
  use_default_colors();
  noecho();
  curs_set(0);
  init_pair(1, COLOR_WHITE, COLOR_GREEN);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);
  init_pair(5, COLOR_BLACK, COLOR_YELLOW);
  init_pair(11, COLOR_RED, COLOR_RED);
  init_pair(12, COLOR_BLUE, COLOR_BLUE);
  init_pair(13, COLOR_CYAN, COLOR_CYAN);
  init_pair(14, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(15, COLOR_WHITE, COLOR_WHITE);
}

void          Ncurses::B_Circle_Yellow(int y, int x, Game::Command cmd)
{
  (void)cmd;
  wattron(BOARD, COLOR_PAIR(5));
  mvwprintw(BOARD, y, x, "O");
  wattroff(BOARD, COLOR_PAIR(5));
}

void          Ncurses::Dead_Ghost(int y, int x)
{
  wattron(BOARD, COLOR_PAIR(15));
  mvwprintw(BOARD, y, x, "O");
  wattroff(BOARD, COLOR_PAIR(15));
}

void          Ncurses::Ghost(int y, int x, int type)
{
  wattron(BOARD, COLOR_PAIR(type));
  mvwprintw(BOARD, y, x, "0");
  wattroff(BOARD, COLOR_PAIR(type));
}


void          Ncurses::B_Circle(int y, int x, Game::Command DIR)
{
  (void)DIR;
  wattron(BOARD, COLOR_PAIR(2));
  mvwprintw(BOARD, y, x, "O");
  wattroff(BOARD, COLOR_PAIR(2));
}

void          Ncurses::S_Star(int y, int x)
{
  mvwprintw(BOARD, y, x, "X");
}

void          Ncurses::S_Dot(int y, int x)
{
  mvwprintw(BOARD, y, x, ".");
}

void 		       Ncurses::B_Dot(int y, int x)
{
  mvwprintw(BOARD, y, x, "*");
}

void          Ncurses::Space(int y, int x)
{
  mvwprintw(BOARD, y, x, " ");
}

void          Ncurses::S_Circle(int y, int x)
{
  wattron(BOARD, COLOR_PAIR(1));
  mvwprintw(BOARD, y, x, "o");
  wattroff(BOARD, COLOR_PAIR(1));
}

void          Ncurses::B_Block(int y, int x)
{
  wattron(BOARD, COLOR_PAIR(4));
  mvwprintw(BOARD, y, x, " ");
  wattroff(BOARD, COLOR_PAIR(4));
}

void          Ncurses::DISPLAY_Score(int _SCORE)
{
  mvwprintw(SCORE, 1, 1, "Score :");
  mvwprintw(SCORE, 1, 9, std::to_string(_SCORE).c_str());
}

void          Ncurses::DISPLAY_Level(int _LVL)
{
  mvwprintw(SCORE, 2, 1, "Level :");
  mvwprintw(SCORE, 2, 9, std::to_string(_LVL).c_str());
}

void          Ncurses::Refresh()
{
  wrefresh(BOARD);
  wrefresh(SCORE);
}

void          Ncurses::Keyboard()
{
  char    key;

  key = getch();
  if (key != ERR)
    {
      if (key == ' ')
        {
          _DIR = Game::Command::PAUSE;
          return ;
        }
      if (key == '\'')
        {
          _DIR = Game::Command::NEXTLIB;
          return ;
        }
      if (key == '(')
        {
          _DIR = Game::Command::NEXTGAME;
          return ;
        }
      if (key == '_')
        {
          _DIR = Game::Command::RESTART;
          return ;
        }
      if (key == '"')
        {
          _DIR = Game::Command::PREVLIB;
          return ;
        }
      if (key == 27)
        {
          key = getch();
          if (key == ERR)
            {
              _DIR = Game::Command::ESCAPE;
              return ;
            }
          key = getch();
          if (key == 'A')
            {
              _DIR = Game::Command::UP;
              return ;
            }
          else if (key == 'B')
            {
              _DIR = Game::Command::DOWN;
              return ;
            }
          else if (key == 'C')
            {
              _DIR = Game::Command::RIGHT;
              return ;
            }
          else if (key == 'D')
            {
              _DIR = Game::Command::LEFT;
              return ;
            }
        }
    }
}

void                     Ncurses::Launcher_Header()
{
  wattron(WIN, A_BOLD);
  mvwprintw(WIN, 10, 42, " .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.   ");
  mvwprintw(WIN, 11, 42, "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |  ");
  mvwprintw(WIN, 12, 42, "| |      __      | || |  _______     | || |     ______   | || |      __      | || |  ________    | || |  _________   | |  ");
  mvwprintw(WIN, 13, 42, "| |     /  \\     | || | |_   __  \\   | || |   .' ___  |  | || |     /  \\     | || | |_   ___ `.  | || | |_   ___  |  | |  ");
  mvwprintw(WIN, 14, 42, "| |    / /\\ \\    | || |   | |__) |   | || |  / .'   \\_|  | || |    / /\\ \\    | || |   | |   `. \\ | || |   | |_  \\_|  | |  ");
  mvwprintw(WIN, 15, 42, "| |   / ____ \\   | || |   |  __ /    | || |  | |         | || |   / ____ \\   | || |   | |    | | | || |   |  _|  _   | |  ");
  mvwprintw(WIN, 16, 42, "| | _/ /    \\ \\_ | || |  _| |  \\ \\_  | || |  \\ `.___.'\\  | || | _/ /    \\ \\_ | || |  _| |___.' / | || |  _| |___/ |  | |  ");
  mvwprintw(WIN, 17, 42, "| ||____|  |____|| || | |____| |___| | || |   `._____.'  | || ||____|  |____|| || | |________.'  | || | |_________|  | |  ");
  mvwprintw(WIN, 18, 42, "| |              | || |              | || |              | || |              | || |              | || |              | |  ");
  mvwprintw(WIN, 19, 42, "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |  ");
  mvwprintw(WIN, 20, 42, " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'   ");
  wattroff(WIN, A_BOLD);
}

std::string              Ncurses::Launcher(std::vector<t_directory> v)
{
  std::string            string;
  WINDOW*                menu_win;
  unsigned long int      n = v.size();
  ITEM**                 items;
  int                    c = 0;
  char                   key;
  MENU*                  menu;
  unsigned long int      pos = 0;
  char str[100];

  items = (ITEM**)calloc(n + 1, sizeof(ITEM*));
  for (std::vector<t_directory>::iterator i = v.begin(); i != v.end(); ++i)
    {
      items[c] = new_item(i->name.c_str(), NULL);
      c = c + 1;
    }
  menu = new_menu(items);
  menu_win = newwin(9, 40, (LINES / 2) - 5, (COLS / 2) - 20);
  box(menu_win, 0, 0);
  mvwprintw(menu_win, 0, 14, "SELECT GAME");
  set_menu_win(menu, menu_win);
  set_menu_sub(menu, derwin(menu_win, 6, 38, 3, 1));
  post_menu(menu);
  wrefresh(WIN);
  wrefresh(menu_win);
  while ((key = getch()) != 10)
    {
     Launcher_Header();
     if (key != ERR)
      {
        if (key == 27)
          {
            key = getch();
            if (key == ERR)
              {
                string.clear();
                return (string);
              }
            key = getch();
            switch(key)
      	     {
               case 'B':
      			      menu_driver(menu, REQ_DOWN_ITEM);
                  if (pos < n - 1)
                    pos = pos + 1;
                  break;
      			   case 'A':
      			      menu_driver(menu, REQ_UP_ITEM);
                  if (pos >= 1)
                    pos = pos - 1;
                  break;
                }
            }
          }
      wrefresh(menu_win);
      wrefresh(WIN);
    }
  echo();
  nodelay(WIN, FALSE);
  mvwprintw(WIN, 45, 80, "Enter your name : ");
  mvwgetstr(WIN, 45, 100, str);
  nodelay(WIN, TRUE);
  noecho();
  wclear(WIN);
  wrefresh(WIN);
  return (v[pos].path);
}

Game::Command    Ncurses::GET_key()
{
  return (_DIR);
}

void             Ncurses::Clear_WIN()
{
  _DIR = Game::Command::NONE;
  wclear(WIN);
}

void                    Ncurses::DISPLAY_background(std::string& path)
{
  (void)path;
}

Ncurses::Ncurses()
{
  _DIR = Game::Command::NONE;
}

Ncurses::~Ncurses()
{
  endwin();
}

extern "C" Ncurses* C_LIB()
{
  return (new Ncurses());
}
