#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__
#include "../buffers/TextureBuffer.h"
#include "../render/TextureUnitManager.h"
#include <GL/glew.h>
#include <string>
#include "ReloadableAsset.h"

class Texture2D : public ReloadableAsset
{
  
public:
   /**
    * Create an RGB texture. (No alpha support, yet...)
    * Will also have support for loading texture metadata
    */
   Texture2D(std::string textureName);

   ~Texture2D();
   /**
    * Enable the texture on the shader
    * @param samplerID the id of the texture sampler
    */
   void enable(GLint samplerID);
   /**
    * Disable the texture on the shader
    */
   void disable();
   /**
    * Get the width of the texture
    * @return the width, in pixels.
    */
   int getWidth();
   /**
    * Get the height of the texture
    * @return the height, in pixels.
    */
   int getHeight();
   /**
    * Get the name of the texture
    * @return the path to the texture
    */
   const std::string getName();
   
   /**
    * Reload this texture. Implemented for ReloadableAsset.
    * Calling Reload will cauase this texture to be pushed onto the GPU.
    */
   void reload();
   




private:
   std::string textureName;
   int width;
   int height;
   TextureBuffer bfr;
   std::shared_ptr<TextureUnit> texUnit;

};


#endif