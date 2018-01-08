//
// Mesh.cpp for MESH in /home/chauvin/Rendu-2017-Epitech/CPP/clone/cpp_arcade/GUIs/OpenGL
// 
// Made by chauvin
// Login   <chauvi_d>
// 
// Started on  Sun Apr  9 22:36:00 2017 chauvin
// Last update Sun Apr  9 22:36:02 2017 chauvin
//

#include "Mesh.hpp"

void Mesh::setup()
{
  glGenVertexArrays(1, &this->VertexArrayID);
  glGenBuffers(1, &this->BufferArrayID);
  glGenBuffers(1, &this->ElementArrayID);
  glBindVertexArray(this->VertexArrayID);
  glBindBuffer(GL_ARRAY_BUFFER, this->BufferArrayID);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementArrayID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
  glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;
  this->setup();
}

void Mesh::Draw(Shader shader)
{
  GLuint diffuseNr = 1;
  GLuint specularNr = 1;

  for (GLuint i = 0; i < this->textures.size(); i++)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      std::stringstream ss;
      std::string number;
      std::string name = this->textures[i].type;
      if(name == "texture_diffuse")
	ss << diffuseNr++;
      else if(name == "texture_specular")
	  ss << specularNr++;
      number = ss.str();
      glUniform1i(glGetUniformLocation(shader.Program, (name + number).c_str()), i);
      glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }
  glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 16.0f);
  glBindVertexArray(this->VertexArrayID);
  glDrawElements(GL_TRIANGLES, (GLsizei) this->indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  for (GLuint i = 0; i < this->textures.size(); i++)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
}

const std::vector<Vertex> &Mesh::getVertices() const
{
  return vertices;
}

void Mesh::setVertices(const std::vector<Vertex> &vertices)
{
  Mesh::vertices = vertices;
}

const std::vector<GLuint> &Mesh::getIndices() const
{
  return indices;
}

void Mesh::setIndices(const std::vector<GLuint> &indices)
{
  Mesh::indices = indices;
}

const std::vector<Texture> &Mesh::getTextures() const
{
  return textures;
}

void Mesh::setTextures(const std::vector<Texture> &textures)
{
  Mesh::textures = textures;
}


