/*
** Sfml.hpp for cpp_arcade in /home/chenne_a/delivery/cpp_arcade/Sfml.hpp
**
** Made by Prenom Nom
** Login   <arthur.chennetier@epitech.eu>
**
** Started on  mer. mars 22 10:37:30 2017 Prenom Nom
** Last update Sun Apr  9 18:41:39 2017 Aubanel Maxime
*/

#ifndef _SFML_HPP_
# define _SFML_HPP_

#include "IGUI.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class SFML : public IGUI
{
 private:
  sf::RenderWindow	WIN;
  sf::RenderWindow	WIN_GAME;
  Game::Command _DIR;
  int 			ratio_x;
  int 			ratio_y;
  std::string		pseudo;

 public:
  void			print_pseudo();
  void			get_pseudo(sf::Event event);
  void		    Init_GUI();
  void		    Init_Game(int, int);
  void      	DISPLAY_Score(int);
  void      	Keyboard();
  std::string	Launcher(std::vector<t_directory>);
  void		    Launcher_Header(sf::Font font);
  void	   	  printGames(std::vector <t_directory> v, int cursor, sf::Font font);
  void	   	  Clear_WIN();
  void        DISPLAY_Level(int);
  void        DISPLAY_background(std::string&);


 public:
  void 		    Ghost(int, int, int);
  void 		    Dead_Ghost(int, int);
  void	      B_Dot(int, int);
  void        Space(int, int);
  void        B_Block(int, int);
  void        S_Circle(int, int);
  void        B_Circle(int, int, Game::Command);
  void        S_Dot(int, int); /* vide */
  void        Refresh();
  void        B_Circle_Yellow(int, int, Game::Command);
  void        S_Star(int, int);


 public:
  Game::Command GET_key();


 public:
  SFML();
  virtual ~SFML();
};

extern "C" SFML* C_LIB();

#endif
