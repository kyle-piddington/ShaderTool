#include "Texture2D.h"
#include <SOIL.h>
#include "../logger/GL_Logger.h"
#include <easyLogging++.h>
#include "../util/FileUtils.h"
#include "ReloadableAsset.h"

//Empty constructor
Texture2D::Texture2D():
bfr(GL_TEXTURE_2D),
width(-1),
height(-1),
texUnit(nullptr),
texType(TextureType::NONE)
{

}

Texture2D::Texture2D(std::string name):
bfr(GL_TEXTURE_2D),
texUnit(nullptr),
texType(TextureType::NONE)
{
   init(TextureConfig(name,GL_RGB,GL_RGB,GL_UNSIGNED_BYTE));
}

Texture2D::Texture2D(TextureConfig config):
   bfr(GL_TEXTURE_2D),
   texUnit(nullptr),
   texType(TextureType::NONE)
  
{
   init(config);
}


void Texture2D::init(TextureConfig config)
{
   this->conf = config;
   ReloadableAsset::init(config.getTextureName());
   int loadType = SOIL_LOAD_RGB;
   
   if(config.getInputFormat() == GL_RGBA || config.getInputFormat() == GL_SRGB_ALPHA)
   {
      loadType = SOIL_LOAD_RGBA;
      bfr.setRepeat(GL_CLAMP_TO_EDGE);
   }
   LOG(ERROR) << "Loading texture" << config.getTextureName();
   std::string textureName = config.getTextureName();
   if(!FileUtils::fExists(textureName))
   {
      LOG(ERROR) << "Could not find texture at " + textureName;
      textureName = "assets/textures/missing_texture.png";
   }
   bfr.setStoreFormat(config.getInputFormat());

   unsigned char* image = SOIL_load_image(textureName.c_str(), &width, &height, 0, loadType);
   bfr.setData(image, width, height, config.getOutputFormat(), config.getDataType());
   SOIL_free_image_data(image);
}

void Texture2D::init(TextureConfig config, const void * data, int texwidth, int texheight)
{

   this->conf = config;
   this->width = texwidth;
   this->height = texheight;
   bfr.setStoreFormat(config.getInputFormat());
   bfr.setRepeat(config.getWrapModeS());
   bfr.setMagnifyFiltering(config.getMagFilter());
   bfr.setMinifyFilter(config.getMinFilter());
   bfr.setData(data, texwidth, texheight, config.getOutputFormat(), config.getDataType());
}

Texture2D::~Texture2D()
{
   if(texUnit != nullptr)
      texUnit->release();
   bfr.unbind();
}

void Texture2D::enable(GLint samplerID)
{
   if(texUnit == nullptr)
   {
      texUnit = std::make_shared<TextureUnit>(TextureUnitManager::requestTextureUnit());
      GL_Logger::LogError("Could not activate texture", glGetError());
   }
   glActiveTexture(texUnit->getGlUnit());  
   bfr.bind();
   glUniform1i(samplerID, texUnit->getTexUnit());
   currentBoundSampler = samplerID;
   GL_Logger::LogError("Could not set texture uniform for " + conf.getTextureName()  + " at location " + std::to_string(samplerID) , glGetError());
}
void Texture2D::disable()
{
   if(texUnit != nullptr)
      texUnit->release();

   bfr.unbind();
   texUnit = nullptr;
}

void Texture2D::reload()
{
   int loadType = SOIL_LOAD_RGB;
   if(conf.getInputFormat() == GL_RGBA || conf.getInputFormat() == GL_SRGB_ALPHA)
   {
      loadType = SOIL_LOAD_RGBA;
      bfr.setRepeat(GL_CLAMP_TO_EDGE);
   }
   std::string textureName = conf.getTextureName();
   if(!FileUtils::fExists(textureName))
   {
      LOG(ERROR) << "Could not find texture at " + textureName;
      textureName = "assets/textures/missing_texture.png";
   }
   bfr.setStoreFormat(conf.getInputFormat());

   unsigned char* image = SOIL_load_image(textureName.c_str(), &width, &height, 0, loadType);
   bfr.setData(image, width, height, conf.getOutputFormat(), conf.getDataType());
   SOIL_free_image_data(image);

}

TextureType::type Texture2D::textureType()
{
   return texType;
}

void Texture2D::setTextureType(TextureType::type tType)
{
   texType = tType;
}
