#ifndef __TEXTURE_CONFIG_H__
#define __TEXTURE_CONFIG_H__
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
   TextureConfig()
   {

   }
   
   TextureConfig(std::string texName):
   texName(texName),
   textureInputFmt(GL_RGB),
   textureOutputFmt(GL_RGB),
   textureDataType(GL_UNSIGNED_BYTE)
   {

   }
   TextureConfig(std::string texName, GLenum inputFmt, GLenum outputFmt, GLenum dataType):
      textureInputFmt(inputFmt),
      textureOutputFmt(outputFmt),
      textureDataType(dataType),
      texName(texName)
   {

   }

   GLenum getInputFormat() const
   {
      return textureInputFmt;
   }
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