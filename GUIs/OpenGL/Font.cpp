//
// Font.cpp for FONT in /home/chauvin/Rendu-2017-Epitech/CPP/clone/cpp_arcade/GUIs/OpenGL
// 
// Made by chauvin
// Login   <chauvi_d>
// 
// Started on  Sun Apr  9 22:35:42 2017 chauvin
// Last update Sun Apr  9 22:35:43 2017 chauvin
//

#include <vector>
#include <glm/vec2.hpp>
#include "Font.hpp"
#include "Shader.hpp"
#include "DDS.hpp"

GLuint FontTextureID;
GLuint FontVertexBufferID;
GLuint FontUVBufferID;
GLuint FontShaderID;
GLuint FontUniformID;

void initFont(const std::string texturePath)
{
  FontTextureID = DDS(texturePath.c_str());
  glGenBuffers(1, &FontVertexBufferID);
  glGenBuffers(1, &FontUVBufferID);
  Shader textShader("./GUIs/OpenGL/TextVertexShader.vertexshader", "./GUIs/OpenGL/TextVertexShader.fragmentshader");
  textShader.Use();
  FontShaderID = textShader.Program;
  FontUniformID = (unsigned int) glGetUniformLocation(FontShaderID, "myTextureSampler" );
}

void printFont(const std::string text, int x, int y, int size)
{
  unsigned int length = (unsigned int) text.size();
  std::vector<glm::vec2> vertices;
  std::vector<glm::vec2> UVs;

  for ( unsigned int i=0 ; i<length ; i++ )
    {
      glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
      glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
      glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
      glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );
      vertices.push_back(vertex_up_left   );
      vertices.push_back(vertex_down_left );
      vertices.push_back(vertex_up_right  );
      vertices.push_back(vertex_down_right);
      vertices.push_back(vertex_up_right);
      vertices.push_back(vertex_down_left);
      char character = text[i];
      float uv_x = (character%16)/16.0f;
      float uv_y = (character/16)/16.0f;
      glm::vec2 uv_up_left    = glm::vec2( uv_x           , uv_y );
      glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, uv_y );
      glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, (uv_y + 1.0f/16.0f) );
      glm::vec2 uv_down_left  = glm::vec2( uv_x           , (uv_y + 1.0f/16.0f) );
      UVs.push_back(uv_up_left   );
      UVs.push_back(uv_down_left );
      UVs.push_back(uv_up_right  );
      UVs.push_back(uv_down_right);
      UVs.push_back(uv_up_right);
      UVs.push_back(uv_down_left);
    }
  glBindBuffer(GL_ARRAY_BUFFER, FontVertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, FontUVBufferID);
  glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);
  glUseProgram(FontShaderID);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, FontTextureID);
  glUniform1i(FontUniformID, 0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, FontVertexBufferID);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, FontUVBufferID);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vertices.size());
  glDisable(GL_BLEND);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}
