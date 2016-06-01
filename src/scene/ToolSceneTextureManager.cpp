#include "ToolSceneTextureManager.h"

ToolSceneTextureManager::ToolSceneTextureManager(std::string texturePath)
{
   loadTextures(path)
}

void ToolSceneTextureManager::loadTextures(std::string path)
{
   std::vector<std::string> pngNames = appendPath(path,DirectoryHandler::listDirectory(path,"png"));
   std::vector<std::string> jpgNames = appendPath(path,DirectoryHandler::listDirectory(path,"jpg"));
   loadTextureByNames(pngNames);
   loadTextureByNames(jpgNames);
}

void ToolSceneTextureManager loadTextureByNames(const std::vector<std::string> & tex)
{
   for (std::vector<std::string>::iterator i = tex.begin(); i != tex.end(); ++i)
   {
      Texture2D newTex(*i);
      textures.push_back(newTex.getTextureID());
   }
}