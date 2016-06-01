#ifndef __TOOLSCENE_TEX_MGR_H__
#define __TOOLSCENE_TEX_MGR_H__
#include <Texture2D.h>
class ToolSceneTextureManager
{
public:
   ToolSceneTextureManager(std::string texturePath);

   void addTexture(Texture2D newTex);
   void addTexture(GLunit textureID);
   const std::vector<GLunit> & getAvaliableTextures();

private:
   void loadTextures();
   std::vector<GLuint> textures;
};
#endif