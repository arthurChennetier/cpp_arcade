//
// Shader.cpp for Shader in /home/chauvin/Rendu-2017-Epitech/CPP/clone/cpp_arcade/GUIs/OpenGL
// 
// Made by chauvin
// Login   <chauvi_d>
// 
// Started on  Sun Apr  9 22:36:55 2017 chauvin
// Last update Sun Apr  9 22:36:55 2017 chauvin
//

#include "Shader.hpp"

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
{
  std::string vCode;
  std::string fCode;
  std::ifstream vSFile;
  std::ifstream fSFile;
  GLuint vertex, fragment;
  GLint success;
  const GLchar* vSCode;
  const GLchar * fSCode;
  
  if (vertexPath == NULL || fragmentPath == NULL)
    return;
  vSFile.open(vertexPath);
  fSFile.open(fragmentPath);
  std::stringstream vShaderStream, fShaderStream;
  vShaderStream << vSFile.rdbuf();
  fShaderStream << fSFile.rdbuf();
  vSFile.close();
  fSFile.close();
  vCode = vShaderStream.str();
  fCode = fShaderStream.str();
  vSCode = vCode.c_str();
  fSCode = fCode.c_str();
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vSCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fSCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  this->Program = glCreateProgram();
  glAttachShader(this->Program, vertex);
  glAttachShader(this->Program, fragment);
  glLinkProgram(this->Program);
  glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::Use()
{
  glUseProgram(this->Program);
}
