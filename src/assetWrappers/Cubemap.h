#ifndef __CUBEMAP_H__
#define __CUBEMAP_H__
#include "ReloadableAsset.h"
#include <vector>
#include "GL_Logger.h"
#include "TextureUnitManager.h"
class CubeMap
{
private:
   struct CubeMapTexture : public ReloadableAsset
   {
      CubeMapTexture(std::string path, GLenum face, GLuint cubemapID);
      virtual void reload();
      private:
         GLuint cubeMapID;
         GLenum face;
   };
   std::vector<CubeMapTexture> textures;
   GLuint cubeMapID;
   /**
    * Create a new cubemap. 
    * Textures should be ordered Right, Left, Top, Buttom, Front, Back
    */
   
public:
   CubeMap();
   ~CubeMap();
   void init(std::vector<std::string> textures);
   void enable(GLint samplerID);
   void disable();
   GLuint getID() const;
   CubeMapTexture *cubeTextures[6];
   std::shared_ptr<TextureUnit> texUnit;


};
#endif