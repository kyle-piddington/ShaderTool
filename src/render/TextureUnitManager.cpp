#include "TextureUnitManager.h"
#include "../logger/GL_Logger.h"
#include <easyLogging++.h>

bool TextureUnitManager::initted = false;
std::priority_queue<TextureUnit, std::vector<TextureUnit>, Compare> TextureUnitManager::unitQueue = std::priority_queue<TextureUnit, std::vector<TextureUnit>, Compare> ();

void TextureUnit::release()
{
   if(active)
   {
      active = false;
      TextureUnitManager::unitQueue.push(TextureUnit(*this));

   }
   else
   {
      LOG(WARNING) << "Texture unit " + std::to_string(texUnit) + " Has already been released!";
   }
}
const int TextureUnit::getTexUnit()
{
   if(!active)
   {
      LOG(WARNING) << "Texture unit " + std::to_string(texUnit)  + " Is not avaliable";
      return -1;
   }
   return texUnit;
}
const GLenum TextureUnit::getGlUnit()
{
   if(!active)
   {
      LOG(WARNING) << "Texture unit " + std::to_string(texUnit)  + " Is not avaliable";
      return GL_TEXTURE0;
   }
   return glUnit;
}
void TextureUnitManager::init()
{

   int texUnits = 16;
   glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &texUnits);
   texUnits -= 1;
   GL_Logger::LogError("[WARN] could not get texunits, defaulting to 16", glGetError());
   
   while(texUnits >= 0)
   {
      TextureUnit unit(texUnits, GL_TEXTURE0 + texUnits);
      unitQueue.push(unit);
      texUnits--;
   }
   TextureUnitManager::initted = true;
}

TextureUnit TextureUnitManager::requestTextureUnit()
{
   if(!TextureUnitManager::initted)
   {
      init();
   }
   if(!unitQueue.empty())
   {
      TextureUnit ret = unitQueue.top();
      unitQueue.pop();
      ret.active = true;
      LOG(INFO) << "Leasing unit " + std::to_string(ret.getTexUnit());
      return ret;
   }
   else
   {
      LOG(ERROR) << "Out of texture untis!";
      exit(-1);
   }
}


