#include "TextureManager.h"
std::unordered_map<std::string, std::shared_ptr<Texture2D>> TextureManager::textures;

std::shared_ptr<Texture2D> getTexture(std::string name)
{
   std::shared_ptr<Shader> ret = nullptr;
   auto preloadedTexture = textures.find(name);
   if(preloadedTexture != textures.end())
   {
      ret =  preloadedTexture->second;
   }
   else
   {
      ret = std::shared_ptr(new Texture2D(name));
      textures[name] = ret;
   }
   return ret;
}
