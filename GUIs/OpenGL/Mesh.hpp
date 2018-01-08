//
// Mesh.hpp for MESH in /home/chauvin/Rendu-2017-Epitech/CPP/clone/cpp_arcade/GUIs/OpenGL
// 
// Made by chauvin
// Login   <chauvi_d>
// 
// Started on  Sun Apr  9 22:36:09 2017 chauvin
// Last update Sun Apr  9 22:36:10 2017 chauvin
//

#ifndef CPP_ARCADE_MESH_HPP
#define CPP_ARCADE_MESH_HPP

#include <assimp/types.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.hpp"

typedef struct 	s_Vertex
{
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
}		Vertex;

typedef struct 	s_Texture
{
  GLuint id;
  std::string type;
  aiString path;
}		Texture;

class Mesh
{
 private:
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<Texture> textures;
  GLuint VertexArrayID;
  GLuint BufferArrayID;
  GLuint ElementArrayID;
  void setup();
 public:
  Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
  void Draw(Shader shader);
  const std::vector<Vertex> &getVertices() const;
  void setVertices(const std::vector<Vertex> &vertices);
  const std::vector<GLuint> &getIndices() const;
  void setIndices(const std::vector<GLuint> &indices);
  const std::vector<Texture> &getTextures() const;
  void setTextures(const std::vector<Texture> &textures);
};


#endif //CPP_ARCADE_MESH_HPP
