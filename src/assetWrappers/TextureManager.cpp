#include "TextureManager.h"
std::unordered_map<std::string, std::shared_ptr<Texture2D>> TextureManager::textures;

std::shared_ptr<Texture2D> TextureManager::getTexture(std::string name)
{
   std::shared_ptr<Texture2D> ret = nullptr;
   auto preloadedTexture = textures.find(name);
   if(preloadedTexture != textures.end())
   {
      ret =  preloadedTexture->second;
   }
   else
   {
      ret = std::shared_ptr<Texture2D>(new Texture2D(name));
      textures[name] = ret;
   }
   return ret;
}
