//
// DDS.cpp for DDS in /home/chauvin/Rendu-2017-Epitech/CPP/clone/cpp_arcade/GUIs/OpenGL
// 
// Made by chauvin
// Login   <chauvi_d>
// 
// Started on  Sun Apr  9 22:35:17 2017 chauvin
// Last update Sun Apr  9 22:35:17 2017 chauvin
//

#include <string>
#include <GL/glew.h>
#include <fstream>

#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844

GLuint DDS(const char *imagepath)
{
  unsigned char header[124];
  std::ifstream fd;
  char filecode[4];

  fd.open(imagepath);
  fd.read(filecode, 4);
  fd.read((char *)(&header), 124);
  unsigned int height      = *(unsigned int*)&(header[8 ]);
  unsigned int width	     = *(unsigned int*)&(header[12]);
  unsigned int linearSize	 = *(unsigned int*)&(header[16]);
  unsigned int mipMapCount = *(unsigned int*)&(header[24]);
  unsigned int fourCC      = *(unsigned int*)&(header[80]);
  unsigned char * buffer;
  unsigned int bufsize;
  bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
  buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
  fd.read((char *)buffer, bufsize);
  fd.close();
  unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
  unsigned int format;
  switch(fourCC)
    {
      case FOURCC_DXT1:
	format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
      break;
      case FOURCC_DXT3:
	format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
      break;
      case FOURCC_DXT5:
	format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
      break;
      default:
	free(buffer);
      return 0;
    }
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
  unsigned int offset = 0;
  for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
      unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
      glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);
      offset += size;
      width  /= 2;
      height /= 2;
      if(width < 1)
	width = 1;
      if(height < 1)
	height = 1;
    }
  free(buffer);
  (void)components;
  return textureID;
}
