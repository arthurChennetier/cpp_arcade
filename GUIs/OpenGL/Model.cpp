//
// Model.cpp for MODEL in /home/chauvin/Rendu-2017-Epitech/CPP/clone/cpp_arcade/GUIs/OpenGL
// 
// Made by chauvin
// Login   <chauvi_d>
// 
// Started on  Sun Apr  9 22:36:27 2017 chauvin
// Last update Sun Apr  9 22:36:27 2017 chauvin
//

#include "Model.hpp"
#include "../../Include/SOIL.h"

Model::Model(GLchar *path)
{
  if (path == NULL)
    return;
  load(path);
}

void Model::Draw(Shader shader)
{
  for(GLuint i = 0; i < meshes.size(); i++)
    meshes[i].Draw(shader);
}

void Model::load(std::string path)
{
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    return;
  this->dir = path.substr(0, path.find_last_of('/'));
  this->Node(scene->mRootNode, scene);
}

void Model::Node(aiNode *node, const aiScene *scene)
{
  for(GLuint i = 0; i < node->mNumMeshes; i++)
    {
      aiMesh* m = scene->mMeshes[node->mMeshes[i]];
      this->meshes.push_back(this->mesh(m, scene));
    }
  for(GLuint i = 0; i < node->mNumChildren; i++)
    {
      this->Node(node->mChildren[i], scene);
    }
}

Mesh Model::mesh(aiMesh *mesh, const aiScene *scene)
{
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<Texture> textures;

  for(GLuint i = 0; i < mesh->mNumVertices; i++)
    {
      Vertex vertex;
      glm::vec3 vector;
      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
      vertex.Position = vector;
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;
      if(mesh->mTextureCoords[0])
	{
	  glm::vec2 vec;
	  vec.x = mesh->mTextureCoords[0][i].x;
	  vec.y = mesh->mTextureCoords[0][i].y;
	  vertex.TexCoords = vec;
	}
      else
	vertex.TexCoords = glm::vec2(0.0f, 0.0f);
      vertices.push_back(vertex);
    }
  for(GLuint i = 0; i < mesh->mNumFaces; i++)
    {
      aiFace face = mesh->mFaces[i];
      for(GLuint j = 0; j < face.mNumIndices; j++)
	indices.push_back(face.mIndices[j]);
    }
      aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
      std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
      std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
  std::vector<Texture> textures;
  for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
      aiString str;
      mat->GetTexture(type, i, &str);
      GLboolean skip = false;
      for(GLuint j = 0; j < textures_loaded.size(); j++)
	{
	  if(std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
	    {
	      textures.push_back(textures_loaded[j]);
	      skip = true;
	      break;
	    }
	}
      if (!skip)
	{
	  Texture texture;
	  texture.id = (GLuint) TFromFile(str.C_Str(), this->dir);
	  texture.type = typeName;
	  texture.path = str;
	  textures.push_back(texture);
	  this->textures_loaded.push_back(texture);
	}
    }
  return textures;
}

const std::vector<Mesh> &Model::getMeshes() const
{
  return meshes;
}

void Model::setMeshes(const std::vector<Mesh> &meshes)
{
  Model::meshes = meshes;
}

const std::string &Model::getDir() const
{
  return dir;
}

void Model::setDir(const std::string &directory)
{
  Model::dir = directory;
}

const std::vector<Texture> &Model::getTextures_loaded() const
{
  return textures_loaded;
}

void Model::setTextures_loaded(const std::vector<Texture> &textures_loaded)
{
  Model::textures_loaded = textures_loaded;
}

GLint TFromFile(const char* path, std::string directory)
{
  std::string filename = std::string(path);
  filename = directory + '/' + filename;
  GLuint textureID;
  glGenTextures(1, &textureID);
  int width,height;
  unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  SOIL_free_image_data(image);
  return textureID;
}
