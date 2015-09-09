#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__
#include "Texture2D.h"
#include <unordered_map>
class TextureManager
{
public:
  static std::shared_ptr<Texture2D> getTexture(std::string path);
private:
  static std::unordered_map<std::string, std::shared_ptr<Texture2D>> textures;

};
#endif