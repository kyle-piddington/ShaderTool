#include "TextureUnitManager.h"
#include "../logger/GL_Logger.h"
#include <easyLogging++.h>

int TextureUnitManager::texIdx = 0;
bool TextureUnitManager::initted = false;
std::vector<TextureUnit> TextureUnitManager::unitQueue;


void TextureUnit::release()
{
   TextureUnitManager::texIdx++;
}
void TextureUnitManager::init()
{

   int texUnits;
   glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &texUnits);
   texUnits -= 1;
   if(GL_Logger::LogError("[WARN] could not get texunits, defaulting to 16", glGetError()))
   {
      texUnits = 15;
   }
   TextureUnitManager::texIdx = texUnits;
   while(texUnits >= 0)
   {
      TextureUnit unit(texUnits, GL_TEXTURE0 + texUnits);
      unitQueue.push_back(unit);
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
      TextureUnit ret = unitQueue[texIdx];
      texIdx--;
      return ret;
   }
   else
   {
      LOG(ERROR) << "Out of texture untis!";
      exit(-1);
   }
}


