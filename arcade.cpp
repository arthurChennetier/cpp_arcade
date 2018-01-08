  /*
** launcher.cpp for arcade in /home/aubanel_m/tek2/arcade/Games
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Thu Mar 09 18:17:07 2017 aubanel_m
// Last update Sun Apr  9 22:20:53 2017 Aubanel Maxime
*/

#include "Include/Protocol.hpp"
#include "Include/IGame.hpp"

int                   isCommand(int cmd)
{
  if (cmd == Game::Command::NEXTLIB
  || cmd == Game::Command::PREVLIB
  || cmd == Game::Command::NEXTGAME)
    return (0);
  return (-1);
}

int                   Gameloop(IGUI *GUI, IGame *GAME)
{
  Game::Command       dir;
  Game::s_board_info	*info;
  int                  command;

  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  std::chrono::high_resolution_clock::time_point t2;
  info = GAME->GET_Board_info();
  GUI->Init_Game(info->height, info->width);
  dir = Game::Command::NONE;
  command = GAME->CYCLE(dir);
  while (command != Game::Command::ESCAPE && command != -1)
    {
      t2 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
      GUI->Keyboard();
      dir = GUI->GET_key();
      GAME->DISPLAY(GUI);
      if (time_span > (std::chrono::duration<double>)0.1 && dir != Game::Command::PAUSE)
        {
          command = GAME->CYCLE(dir);
          t1 = std::chrono::high_resolution_clock::now();
        }
      if (command == Game::Command::RESTART)
        {
          GAME->RESTART();
        }
      if (isCommand(command) == 0)
        {
          GUI->Clear_WIN();
          return (command);
        }
    }
  GUI->Clear_WIN();
  return (command);
}

std::vector<t_directory>       Game_Finder(std::string string)
{
  DIR                       *dir;
  struct dirent             *ent;
  std::vector<t_directory>       v;
  std::vector<t_directory>       t;
  t_directory *tmp = new t_directory;

  if ((dir = opendir (string.c_str())) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      if (ent->d_type == DT_DIR)
        {
          if (ent->d_name[0] != '.')
            {
              t = Game_Finder(string + ent->d_name);
              for (std::vector<t_directory>::iterator i = t.begin(); i != t.end(); ++i)
                {
                  tmp->path = std::string(ent->d_name) + "/" + std::string(i->path);
                  tmp->name = i->name;
                  tmp->file_name = i->file_name;
                  v.push_back(*tmp);
                }
            }
        }
      if (std::string(ent->d_name).find(".so") != std::string::npos)
        {
          tmp->path = ent->d_name;
          tmp->name = std::string(ent->d_name).substr(0, std::string(ent->d_name).size() - 3);
          tmp->file_name = ent->d_name;
          v.push_back(*tmp);
        }
    }
    closedir (dir);
  }
  return (v);
}


std::vector<t_directory>       Lib_Finder(std::string string)
{
  DIR                       *dir;
  struct dirent             *ent;
  std::vector<t_directory>       v;
  std::vector<t_directory>       t;
  t_directory *tmp = new t_directory;

  if ((dir = opendir (string.c_str())) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      if (ent->d_type == DT_DIR)
        {
          if (ent->d_name[0] != '.')
            {
              t = Game_Finder(string + ent->d_name);
              for (std::vector<t_directory>::iterator i = t.begin(); i != t.end(); ++i)
                {
                  tmp->path = std::string(ent->d_name) + "/" + std::string(i->path);
                  tmp->name = i->name;
                  tmp->file_name = i->file_name;
                  v.push_back(*tmp);
                }
            }
        }
      if (std::string(ent->d_name).find(".so") != std::string::npos)
        {
          tmp->path = ent->d_name;
          tmp->name = std::string(ent->d_name).substr(0, std::string(ent->d_name).size() - 3);
          tmp->file_name = ent->d_name;
          v.push_back(*tmp);
        }
    }
    closedir (dir);
  }
  return (v);
}


IGUI*      load_library(std::string path)
{
  void*   Gui;
  IGUI    *(*GET_IGUI)();
  IGUI    *GUI;

  Gui = dlopen(path.c_str(), RTLD_LAZY | RTLD_NODELETE);
  if (!Gui)
    {
      std::cout << dlerror() << '\n';
      printf("error\n");
      return (NULL);
    }
  GET_IGUI = (IGUI*(*)()) dlsym(Gui, "C_LIB");
  GUI = (GET_IGUI)();
  dlclose(Gui);
  return (GUI);
}

IGame*      load_game(std::string path)
{
  void*   Game;
  IGame   *(*GET_GAME)();
  IGame   *GAME;

  Game = dlopen(path.c_str(), RTLD_LAZY | RTLD_NODELETE);
  if (!Game)
    {
      std::cout << dlerror() << '\n';
      printf("error\n");
      return (NULL);
    }
  GET_GAME = (IGame*(*)()) dlsym(Game, "C_GAME");
  GAME = (GET_GAME)();
  dlclose(Game);
  return (GAME);
}

void      Error(IGUI *gui, IGame *game)
{
  if (gui != NULL)
    delete gui;
  if (game != NULL)
    delete game;
}

int       main(int ac, char **av)
{
  IGame   *GAME = NULL;
  IGUI    *GUI;

  std::string path = "games/";
  std::string path_lib = "lib/";
  int command;
  int poslib = 0;

  if (ac < 2)
    return (-1);
  t_directory *new_;

  new_ = new t_directory;
  std::vector<t_directory> v = Game_Finder(path);
  std::vector<t_directory> vlib = Lib_Finder(path_lib);
  GUI = load_library(av[1]);
  if (GUI == NULL)
    return (-1);
  for (std::vector<t_directory>::iterator i = vlib.begin(); i != vlib.end(); ++i)
    {
      if ((path_lib + i->path).compare(std::string(av[1])) == 0)
        {
          new_->name = i->name;
          new_->path = i->path;
          new_->file_name = i->file_name;
          vlib.erase(i);
          break;
        }
    }
  if (vlib.size() == 0)
    return (-1);
  vlib.push_back(*new_);
  std::reverse(vlib.begin(), vlib.end());
  while (1)
    {
      GUI->Init_GUI();
      std::string str = GUI->Launcher(v);
      if (str.empty())
        {
          Error(GUI, GAME);
          return (-1);
        }
      GAME = load_game(path + str);
      if (GAME == NULL)
        {
          Error(GUI, GAME);
          return (-1);
        }
      while (1)
        {
          command = Gameloop(GUI, GAME);
          if (command == Game::Command::NEXTLIB)
            {
              delete GUI;
              poslib = poslib + 1;
              if ((unsigned int)poslib == vlib.size())
                poslib = 0;
              GUI = load_library(path_lib + vlib[poslib].path);
            }
          if (command == Game::Command::PREVLIB)
            {
              delete GUI;
              poslib = poslib -1;
              if (poslib == -1)
                poslib = vlib.size() - 1;
              GUI = load_library(path_lib + vlib[poslib].path);
            }
          if (command == Game::Command::ESCAPE || command == -1)
            break;
        }
    }
  return (0);
}
