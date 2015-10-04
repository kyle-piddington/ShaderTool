#ifndef __TEXTURE_CONFIG_H__
#define __TEXTURE_CONFIG_H__
/**
 * TextureConfig is a configuration object allowing for the customization
 * and creation of new textures.
 */
class TextureConfig
{
   //How the texture should be in out (GL_RGB, GL_RGBA, GL_SRGB etc)
   GLenum textureInputFmt;
   //How the texture should be read out
   GLenum textureOutputFmt;
   //How the texture should be stored
   GLenum textureDataType;
   std::string texName;
public:
   /**
    * Create a new Texture configuration object, with no settings.
    */
   TextureConfig()
   {

   }
   /**
    * Create a new texture configuration object with a textue path.
    * The texture will use GL_RGB for it's input and storage types, and 
    GL_Unsigned_Byte for it's data read type.
    */
   TextureConfig(std::string texName):
   texName(texName),
   textureInputFmt(GL_RGB),
   textureOutputFmt(GL_RGB),
   textureDataType(GL_UNSIGNED_BYTE)
   {

   }
   /**
    * Create a new Texture configuration with a texture path, and 
    * internal storage details
    */
   TextureConfig(std::string texName, GLenum inputFmt, GLenum outputFmt, GLenum dataType):
      textureInputFmt(inputFmt),
      textureOutputFmt(outputFmt),
      textureDataType(dataType),
      texName(texName)
   {

   }

   /**
    * Return the input format specificed by this configuration
    * @return the format.
    */
   GLenum getInputFormat() const
   {
      return textureInputFmt;
   }
   /**
    * Return the output format of this texture specificed by the configuration
    * The output format describes what range of values and kinds of values
    * the GPU should expect when sampling the texture configured by this object.
    * @return the output format
    */
   GLenum getOutputFormat() const
   {
      return textureOutputFmt;
   }
   GLenum getDataType() const
   {
      return textureDataType;
   }
   std::string getTextureName() const
   {
      return texName;
   }


};
#endif