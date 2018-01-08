/*
** Sfml.cpp for cpp_arcade in /home/chenne_a/delivery/cpp_arcade/Sfml.cpp
**
** Made by Prenom Nom
** Login   <arthur.chennetier@epitech.eu>
**
** Started on  mer. mars 22 10:37:04 2017 Prenom Nom
** Last update Sun Apr  9 22:23:41 2017 Aubanel Maxime
*/

#include "../../Include/Sfml.hpp"
#include "../../Buildings/SFML/include/SFML/Graphics/Color.hpp"
#include "../../Buildings/SFML/include/SFML/Window/Keyboard.hpp"
#include "../../Buildings/SFML/include/SFML/Window/Event.hpp"

void		SFML::Init_Game(int x, int y)
{
  this-> ratio_x = 780 / x;
  this-> ratio_y = 780 / y;
  this->WIN_GAME.create(sf::VideoMode(1600, 1000), "SFML");
  this->_DIR = Game::Command::NONE;
  this->WIN_GAME.clear(sf::Color::Black);
}

void		SFML::Init_GUI()
{
  this->WIN.create(sf::VideoMode(1600, 1000), "SFML");
}

/* depart du tableau : x = 500 , y = 150  13 de largeur/hauteur  30 * 30
 * 780 * 780 */

void 		SFML::Dead_Ghost(int y, int x)
{
  sf::Sprite 	sprite;
  sf::Texture	texture;

  if (!texture.loadFromFile("./GUIs/SFML/sprites/dead_ghost.png"))
    {
      std::cerr << "Can't load dead_ghost.png file" << std::endl;
      exit(0);
    }
  sprite.setTexture(texture);
  sprite.setScale(sf::Vector2f(ratio_x / sprite.getLocalBounds().width,
			       ratio_y / sprite.getLocalBounds().height));
  sprite.setPosition(x * ratio_x + 500, y * ratio_y + 150);
  this->WIN_GAME.draw(sprite);
}

void 		SFML::Ghost(int y, int x, int type)
{
  sf::Sprite 	sprite;
  sf::Texture	texture;

  if (type == 11)
    {
      if (!texture.loadFromFile("./GUIs/SFML/sprites/red_ghost.png"))
	{
	  std::cerr << "Can't load red_ghost.png file" << std::endl;
	  exit(0);
	}
    }
  else if (type == 12)
    {
      if (!texture.loadFromFile("./GUIs/SFML/sprites/blue_ghost.png"))
	{
	  std::cerr << "Can't load blue_ghost.png file" << std::endl;
	  exit(0);
	}
    }
  else if (type == 13)
    {
      if (!texture.loadFromFile("./GUIs/SFML/sprites/orange_ghost.png"))
	{
	  std::cerr << "Can't load orange_ghost.png file" << std::endl;
	  exit(0);
	}
    }
  else if (type == 14)
    {
      if (!texture.loadFromFile("./GUIs/SFML/sprites/pink_ghost.png"))
	{
	  std::cerr << "Can't load pink_ghost.png file" << std::endl;
	  exit(0);
	}
    }
  sprite.setTexture(texture);
  sprite.setScale(sf::Vector2f(ratio_x / sprite.getLocalBounds().width,
			       ratio_y / sprite.getLocalBounds().height));
  sprite.setPosition(x * ratio_x + 500, y * ratio_y + 150);
  this->WIN_GAME.draw(sprite);
}

void		SFML::B_Circle(int y, int x, Game::Command DIR)
{
  sf::Sprite 	sprite;
  sf::Texture	texture;

  if (DIR == Game::Command::UP)
    {
      if (!texture.loadFromFile("./GUIs/SFML/sprites/head_up.png"))
	{
	  std::cerr << "Can't load head_up.png file" << std::endl;
	  exit(0);
	}
    }
  else if (DIR == Game::Command::DOWN)
    {
      if (!texture.loadFromFile("./GUIs/SFML/sprites/head_down.png"))
	{
	  std::cerr << "Can't load head_down.png file" << std::endl;
	  exit(0);
	}
    }
  else if (DIR == Game::Command::RIGHT)
    {
      if (!texture.loadFromFile("./GUIs/SFML/sprites/head_right.png"))
	{
	  std::cerr << "Can't load head_right.png file" << std::endl;
	  exit(0);
	}
    }
  else if (DIR == Game::Command::LEFT)
    {
      if (!texture.loadFromFile("./GUIs/SFML/sprites/head_left.png"))
	{
	  std::cerr << "Can't load head_left.png file" << std::endl;
	  exit(0);
	}
    }
  sprite.setTexture(texture);
  sprite.setScale(sf::Vector2f(ratio_x / sprite.getLocalBounds().width,
			       ratio_y / sprite.getLocalBounds().height));
  sprite.setPosition(x * ratio_x + 500, y * ratio_y + 150);
  this->WIN_GAME.draw(sprite);
}

void		SFML::Space(int y, int x)
{
  y = y;
  x = x;
}

void		SFML::S_Circle(int y, int x)
{
  sf::CircleShape	circle(ratio_x / 2);

  circle.setFillColor(sf::Color(52, 172, 112));
  circle.setPosition(x * ratio_x + 500, y * ratio_y + 150);
  circle.setOutlineThickness(2);
  circle.setOutlineColor(sf::Color::Black);
  this->WIN_GAME.draw(circle);
}

void		SFML::B_Block(int y, int x)
{
  sf::RectangleShape rectangle(sf::Vector2f(ratio_x, ratio_y));

  rectangle.setPosition(x * ratio_x + 500, y * ratio_y + 150);
  rectangle.setFillColor(sf::Color::Blue);
  this->WIN_GAME.draw(rectangle);
}

void		SFML::S_Dot(int y, int x)
{
  sf::CircleShape	circle(2);

  circle.setFillColor(sf::Color(242, 249, 248));
  circle.setPosition(x * ratio_x + 500 + ratio_x / 2, y * ratio_y + 150 + ratio_y / 2);
  this->WIN_GAME.draw(circle);
}

void 		SFML::B_Dot(int y, int x)
{
  sf::CircleShape	circle(4);

  circle.setFillColor(sf::Color(242, 249, 248));
  circle.setPosition(x * ratio_x + 500 + ratio_x / 2, y * ratio_y + 150 + ratio_y / 2);
  this->WIN_GAME.draw(circle);
}

void		SFML::B_Circle_Yellow(int y, int x, Game::Command cmd)
{
  sf::CircleShape	circle(10);

  (void)cmd;
  circle.setFillColor(sf::Color(234, 242, 22));
  circle.setPosition(x * ratio_x + 503, y * ratio_y + 153);
  this->WIN_GAME.draw(circle);
}

void		SFML::S_Star(int y, int x)
{
  sf::Sprite sprite;
  sf::Texture	texture;

  if (!texture.loadFromFile("./GUIs/SFML/sprites/big_pomme.png"))
    {
      std::cerr << "Can't load big_pomme.png file" << std::endl;
      exit(0);
    }
  sprite.setTexture(texture);
  sprite.setScale(sf::Vector2f(ratio_x / sprite.getLocalBounds().width,
			       ratio_y / sprite.getLocalBounds().height));
  sprite.setPosition(x * ratio_x + 500, y * ratio_y + 150);
  this->WIN_GAME.draw(sprite);
}

void		SFML::DISPLAY_background(std::string &path)
{
  sf::Texture		grass;
  sf::Texture		wall;
  sf::Sprite 		w_sprite;
  sf::Sprite 		g_sprite;

  path = path;
  this->WIN_GAME.clear(sf::Color::Black);
  if (!path.compare("pac"))
    return ;
  if (!wall.loadFromFile("./GUIs/SFML/sprites/wall.png"))
    {
      std::cerr << "Can't load wall.png file" << std::endl;
      exit(0);
    }
  if (!grass.loadFromFile("./GUIs/SFML/sprites/ecaille.png"))
    {
      std::cerr << "Can't load ecaille.png file" << std::endl;
      exit(0);
    }
  w_sprite.setTexture(wall);
  w_sprite.setPosition(500, 150);
  this->WIN_GAME.draw(w_sprite);
  g_sprite.setTexture(grass);
  g_sprite.setPosition(530, 178);
  this->WIN_GAME.draw(g_sprite);
}

void		SFML::DISPLAY_Score(int _Score)
{
  sf::Font	font;
  sf::Text	text;
  char 		buf[100];

  sprintf(buf, "Score: %d", _Score);
  std::string	score(buf);
  if (!font.loadFromFile("./GUIs/SFML/font/ARCADE.TTF"))
    {
      std::cerr << "Can't load ARCADE.tff file" << std::endl;
      exit(0);
    }
  text.setFont(font);
  text.setPosition(100, 300);
  text.setString(score.c_str());
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::White);
  this->WIN_GAME.draw(text);
}

void		SFML::DISPLAY_Level(int lvl)
{
  sf::Font	font;
  sf::Text	text;
  char 		buf[100];

  sprintf(buf, "Level: %d", lvl);
  std::string	score(buf);
  if (!font.loadFromFile("./GUIs/SFML/font/ARCADE.TTF"))
    {
      std::cerr << "Can't load ARCADE.TTF file" << std::endl;
      exit(0);
    }
  text.setFont(font);
  text.setPosition(100, 200);
  text.setString(score.c_str());
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::White);
  this->WIN_GAME.draw(text);
}

void		SFML::Refresh()
{
  this->WIN_GAME.display();
}

void		SFML::Keyboard()
{
  sf::Event	event;

  while (this->WIN_GAME.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	{
	  this->WIN_GAME.close();
	  exit(0);
	}
      if (event.type == sf::Event::KeyPressed)
	{
	  if (event.key.code == sf::Keyboard::Down)
	    this->_DIR = Game::Command::DOWN;
	  else if (event.key.code == sf::Keyboard::Up)
	    this->_DIR = Game::Command::UP;
	  else if (event.key.code == sf::Keyboard::Right)
	    this->_DIR = Game::Command::RIGHT;
	  else if (event.key.code == sf::Keyboard::Left)
	    this->_DIR = Game::Command::LEFT;
    else if (event.key.code == sf::Keyboard::Space)
  	  this->_DIR = Game::Command::PAUSE;
	  else if (event.key.code == sf::Keyboard::Escape)
	    _DIR = Game::Command::ESCAPE;
    else if (event.key.code == sf::Keyboard::Quote)
      _DIR = Game::Command::NEXTLIB;
    else if (event.key.code == sf::Keyboard::Num3)
      _DIR = Game::Command::PREVLIB;
	  else if (event.key.code == sf::Keyboard::Num8)
	    _DIR = Game::Command::RESTART;
	}
    }
}

void		SFML::Launcher_Header(sf::Font font)
{
  sf::Text	text;

  text.setFont(font);
  text.setPosition(730, 200);
  text.setString("Select game");
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::Red);
  this->WIN.draw(text);
}

void		SFML::printGames(std::vector <t_directory> v, int cursor, sf::Font font)
{
  int		y = 300;
  int		inc = 0;

  for (std::vector<t_directory>::iterator i = v.begin(); i != v.end(); ++i)
    {
      sf::Text	text;
      text.setFont(font);
      text.setPosition(730, y);
      text.setString(i->name.c_str());
      text.setCharacterSize(40);
      text.setFillColor(sf::Color::White);
      if (inc == cursor)
	text.setStyle(sf::Text::Underlined);
      this->WIN.draw(text);
      inc++;
      y = y + 50;
    }
}

void 		SFML::get_pseudo(sf::Event event)
{
  char 		buf[100];
  char 		c;

  if (event.text.unicode < 128)
    {
      c = event.text.unicode;
      sprintf(buf, "%c", c);
      pseudo += c;
    }
}

void 		SFML::print_pseudo()
{
  sf::Text	text;
  sf::Font	font;

  if (!font.loadFromFile("./GUIs/SFML/font/Absolute.ttf"))
    {
      std::cerr << "Can't load Absolute.tff file" << std::endl;
      exit(0);
    }
  text.setFont(font);
  text.setPosition(730, 550);
  text.setString("Enter your game name");
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::White);
  this->WIN.draw(text);
  text.setFont(font);
  text.setPosition(730, 600);
  text.setString(pseudo.c_str());
  text.setCharacterSize(40);
  text.setFillColor(sf::Color::White);
  this->WIN.draw(text);
}

std::string	SFML::Launcher(std::vector <t_directory> v)
{
  sf::Font	font;
  std::string	string;
  int		cursor = 0;
  int		nbr_games = 0;

  pseudo = "";
  if (!font.loadFromFile("./GUIs/SFML/font/Absolute.ttf"))
    {
      std::cerr << "Can't load Absolute.tff file" << std::endl;
      exit(0);
    }
  for (std::vector<t_directory>::iterator it = v.begin(); it != v.end(); ++it)
    nbr_games++;
  while (this->WIN.isOpen())
    {
      sf::Event	event;
      while (this->WIN.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    this->WIN.close();
	  if (event.type == sf::Event::KeyPressed)
	    {
	      if (event.key.code == sf::Keyboard::Down && cursor < nbr_games - 1)
		cursor++;
	      else if (event.key.code == sf::Keyboard::Up && cursor > 0)
		cursor--;
	      else if (event.key.code == sf::Keyboard::Return)
		{
		  this->WIN.close();
		  return (v[cursor].path);
		}
	      else if (event.key.code == sf::Keyboard::Escape)
		{
		  this->WIN.close();
		  exit(0);
		}
	    }
	  if (event.type == sf::Event::TextEntered)
	    get_pseudo(event);
	}
      this->WIN.clear(sf::Color::Black);
      this->print_pseudo();
      this->Launcher_Header(font);
      this->printGames(v, cursor, font);
      this->WIN.display();
    }
  string.clear();
  return string;
}

Game::Command    SFML::GET_key()
{
  return (_DIR);
}

void		SFML::Clear_WIN()
{
  this->WIN_GAME.close();
}

SFML::SFML()
{
  this->_DIR = Game::Command::UP;
}

SFML::~SFML()
{
  this->WIN_GAME.close();
}

extern "C" SFML* C_LIB()
{
  return (new SFML());
}
