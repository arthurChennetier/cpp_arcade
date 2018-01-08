//
// Model.hpp for MODEL in /home/chauvin/Rendu-2017-Epitech/CPP/clone/cpp_arcade/GUIs/OpenGL
// 
// Made by chauvin
// Login   <chauvi_d>
// 
// Started on  Sun Apr  9 22:36:21 2017 chauvin
// Last update Sun Apr  9 22:36:21 2017 chauvin
//

#ifndef CPP_ARCADE_MODEL_HPP
#define CPP_ARCADE_MODEL_HPP

// STD
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

//GL
#include <GL/glew.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"

class Model
{
  std::vector<Mesh> meshes;
  std::string dir;
  std::vector<Texture> textures_loaded;
  void load(std::string path);
  void Node(aiNode* node, const aiScene* scene);
  Mesh mesh(aiMesh* mesh, const aiScene* scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
 public:
  Model(GLchar *path);
  void Draw(Shader shader);
  const std::vector<Mesh> &getMeshes() const;
  void setMeshes(const std::vector<Mesh> &meshes);
  const std::string &getDir() const;
  void setDir(const std::string &directory);
  const std::vector<Texture> &getTextures_loaded() const;
  void setTextures_loaded(const std::vector<Texture> &textures_loaded);
};

GLint TFromFile(const char* path, std::string directory);

#endif //CPP_ARCADE_MODEL_HPP
