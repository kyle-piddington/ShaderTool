#include "CubeMap.h"
#include <SOIL/SOIL.h>
#include <easylogging++.h>
#include "../util/FileUtils.h"

CubeMap::CubeMapTexture::CubeMapTexture(std::string path, GLenum face, GLuint cubeMapID) :
   ReloadableAsset(path),
   face(face),
   cubeMapID(cubeMapID)
   {
      int width, height;
      if(!FileUtils::fExists(path))
      {
         LOG(ERROR) << "Could not find texture at " + path;
         path = "assets/textures/missing_texture.png";
      }
      unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
      glTexImage2D(
          face, 
           0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
       );
       GL_Logger::LogError("Could not add face to cubemap");
   }
void CubeMap::CubeMapTexture::reload()
{
   int width, height;
   std::string path = getPath();
   if(!FileUtils::fExists(path))
   {
         LOG(ERROR) << "Could not find texture at " + path;
         path = "assets/textures/missing_texture.png";
   }
   unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
   glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID);
   glTexImage2D(
          face, 
           0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
       );
   GL_Logger::LogError("Could not reload face to cubemap");
   glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}

CubeMap::CubeMap():
cubeMapID(0),
texUnit(nullptr)
{

}
CubeMap::~CubeMap()
{
   for(int i = 0; i < 6; i++)
   {
      if(cubeTextures[i] != nullptr)
         delete cubeTextures[i];
   }
}

void CubeMap::init(std::vector<std::string> texturePaths)
{
   glGenTextures(1, &cubeMapID);
   glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID);
   GL_Logger::LogError("Could not generate cubemap ", glGetError());
   int numTextures = 0;
   for (std::vector<std::string>::iterator i = texturePaths.begin(); i != texturePaths.end(); ++i)
   {
      cubeTextures[numTextures] = new CubeMapTexture(*i,GL_TEXTURE_CUBE_MAP_POSITIVE_X + numTextures,cubeMapID);
      numTextures++;
   }
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  
   glBindTexture(GL_TEXTURE_CUBE_MAP,0);
}

void CubeMap::enable(GLint samplerID)
{
   if(texUnit == nullptr)
   {
     texUnit = std::make_shared<TextureUnit>(TextureUnitManager::requestTextureUnit());
     glActiveTexture(texUnit->getGlUnit());
     GL_Logger::LogError("Could not activate texture", glGetError());
   }
   glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapID);
   glUniform1i(samplerID, texUnit->getTexUnit());
   GL_Logger::LogError("Could not set texture uniform", glGetError());
}

void CubeMap::disable()
{
   if(texUnit != nullptr)
      texUnit->release();
   glBindTexture(GL_TEXTURE_CUBE_MAP,0);
   texUnit = nullptr;
}



GLuint CubeMap::getID() const
{
   return cubeMapID;

}
