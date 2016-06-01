#ifndef __TEXTURE2D_H__
#define __TEXTURE2D_H__
#include "../buffers/TextureBuffer.h"
#include "../render/TextureUnitManager.h"
#include <GL/glew.h>
#include <string>
#include "ReloadableAsset.h"
#include "TextureConfig.h"
namespace TextureType
{
  enum type
  {
    NONE = -1,
    DIFFUSE = 0,
    SPECULAR = 1
  };
}
class Texture2D : public ReloadableAsset
{

public:
   /**
    * Create an RGB texture. (No alpha support, yet...)
    * Will also have support for loading texture metadata
    */
   
   //Create a texture object without initting it.
   Texture2D();
   Texture2D(std::string textureName);
   Texture2D(TextureConfig config);



  void init(TextureConfig cfg);
  
  /**
   * Init the texture with some custom data
   * @param cfg  the texture configuration
   * @param data the data to init the texture buffer with.
   */
  void init(TextureConfig cfg, const void * data, int width, int height);
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

   void setTextureType(TextureType::type texType);

   TextureType::type textureType();

   /** 
    * Retrieve the internal id of a texture
    */
   GLuint getTextureID() const;
   




private:
   int width;
   int height;
   TextureConfig conf;
   TextureBuffer bfr;
   TextureType::type texType;
   GLint currentBoundSampler;
   std::shared_ptr<TextureUnit> texUnit;

};


#endif