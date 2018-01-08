//
// Shader.hpp for SHADER in /home/chauvin/Rendu-2017-Epitech/CPP/clone/cpp_arcade/GUIs/OpenGL
// 
// Made by chauvin
// Login   <chauvi_d>
// 
// Started on  Sun Apr  9 22:37:00 2017 chauvin
// Last update Sun Apr  9 22:37:00 2017 chauvin
//

#ifndef CPP_ARCADE_SHADER_HPP
#define CPP_ARCADE_SHADER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class Shader
{
 public:
  GLuint Program;
  Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
  void Use();
};


#endif //CPP_ARCADE_SHADER_HPP
