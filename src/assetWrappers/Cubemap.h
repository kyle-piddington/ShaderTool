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
      CubeMapTexture(std::string path, GLenum face, const CubeMap * cubemap);
      virtual void reload();
      private:
         const CubeMap * cubeMap;
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
   void init(std::vector<std::string> textures);
   void enable(GLint samplerID);
   void disable();
   GLuint getID() const;
   std::shared_ptr<TextureUnit> texUnit;


};
#endif