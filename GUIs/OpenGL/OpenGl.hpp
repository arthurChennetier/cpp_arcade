//
// OpenGl.hpp for OPENGL in /home/chauvin/Rendu-2017-Epitech/CPP/clone/cpp_arcade/GUIs/OpenGL
// 
// Made by chauvin
// Login   <chauvi_d>
// 
// Started on  Sun Apr  9 22:36:47 2017 chauvin
// Last update Sun Apr  9 22:36:48 2017 chauvin
//

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/ext.hpp>

// Include AssImp
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

// STD
#include <iostream>
#include <vector>
#include <cstring>

#include "../../Include/IGUI.hpp"
#include "Shader.hpp"
#include "Model.hpp"

#ifndef CPP_ARCADE_OPENGL_HPP
#define CPP_ARCADE_OPENGL_HPP

class OpenGl : public IGUI
{
 private:
  Shader 	modelShader = Shader(nullptr, nullptr);
  Model		apple = Model(nullptr);
  Model		body = Model(nullptr);
  Model		head = Model(nullptr);
  Model		ground = Model(nullptr);
  Model		Wall = Model(nullptr);
  Model		Food = Model(nullptr);
  Model		Cherry = Model(nullptr);
  Model		Pacman = Model(nullptr);
  Model		Deadghost = Model(nullptr);
  Model		pacGhost = Model(nullptr);
  float 	horizontalAngle;
  float 	verticalAngle;
  float 	FoV;
  float 	speed;
  float 	mouseSpeed;
  glm::vec3	position;
  GLuint 	Width;
  GLuint	Height;
  GLFWwindow*	window;
  GLuint 	VertexArrayID;
  glm::mat4 	Projection;
  glm::mat4 	model;
  glm::mat4 	View;
  Game::Command _DIR;

 public:
  const glm::vec3 &getPosition() const;
  void 	setPosition(const glm::vec3 &position);
  float getMouseSpeed() const;
  void 	setMouseSpeed(float mouseSpeed);
  float getHorizontalAngle() const;
  float getVerticalAngle() const;
  void 	setHorizontalAngle(float horizontalAngle);
  void 	setVerticalAngle(float verticalAngle);
  float getFoV() const;
  void 	setFoV(float FoV);
  void 	set_DIR(Game::Command _DIR);

  GLuint getWidth() const;

  void setWidth(GLuint Width);

  GLuint getHeight() const;

  void setHeight(GLuint Height);

 public:
  virtual void 		Init_GUI();
  virtual void 		Init_Game(int, int);
  virtual void 		DISPLAY_Score(int);
  virtual void 		Keyboard();
  virtual std::string	Launcher(std::vector<t_directory>);
  virtual void 		Clear_WIN();
  virtual void 		DISPLAY_Level(int);

  virtual void 		    Dead_Ghost(int, int);
  virtual void 		    Ghost(int, int, int);
  virtual void		Space(int, int){}; // Empty
  virtual void		B_Block(int, int); // Mur Pacman
  virtual void		S_Circle(int, int); // Corp Snake
  virtual void    	B_Circle(int, int, Game::Command);
  virtual void		S_Dot(int, int); // PacGom
  virtual void    	B_Dot(int, int);
  virtual void		Refresh();
  virtual void		B_Circle_Yellow(int, int, Game::Command); // Pac Pac
  virtual void		S_Star(int, int); // Champi Snake
  virtual void        	DISPLAY_background(std::string&);
  virtual Game::Command	GET_key();

  OpenGl();
  virtual	~OpenGl();
  void		game_view();
  void 		printGames(std::vector<t_directory>, int);
};

extern "C" OpenGl* C_LIB();

#endif //CPP_ARCADE_OPENGL_HPP
