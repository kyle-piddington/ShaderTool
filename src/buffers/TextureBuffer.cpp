#include "TextureBuffer.h"
#include "../logger/GL_Logger.h"


TextureBuffer::TextureBuffer(GLenum textureType):
   SWrapType(GL_REPEAT),
   TWrapType(GL_REPEAT),
   magnifyFilter(GL_LINEAR),
   minifyFilter(GL_LINEAR_MIPMAP_LINEAR),
   textureType(textureType),
   storeFmt(GL_RGB)
{
   borderColor[0] = 1.0;
   borderColor[1] = 0.0;
   borderColor[2] = 0.0;
   borderColor[3] = 1.0;
   glGenTextures(1, &textureID);
   glBindTexture(textureType, textureID);
   GL_Logger::LogError("Could not bind texture", glGetError());
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, SWrapType);
   GL_Logger::LogError("Could not set S wrap ", glGetError());
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TWrapType);
   GL_Logger::LogError("Could not set T wrap ", glGetError());
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magnifyFilter);
   GL_Logger::LogError("Could not set magnify filter (Don't use a mimpmap filter!)", glGetError());
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minifyFilter);
   GL_Logger::LogError("Could not set minify filter ", glGetError());
   glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
   GL_Logger::LogError("Could not set border color ", glGetError());

   glBindTexture(textureType, 0);

}

/**
 * @TODO Add memory management for deleting the texture
 */
TextureBuffer::~TextureBuffer()
{

}

int TextureBuffer::setData(const void * img, int width, int height, GLint dataFmt, GLenum dataType, bool generateMipMaps)
{
   int check = 0;
   glBindTexture(textureType, textureID);
   glTexImage2D(textureType, 0, storeFmt, width, height, 0, dataFmt, dataType, img);
   check |= GL_Logger::LogError("Could not bind texture data", glGetError());
   if(generateMipMaps)
   {
      glGenerateMipmap(textureType);
      check |= GL_Logger::LogError("Could not generate mipmap data", glGetError());
   
   }
   glBindTexture(textureType, 0);
   return check;
}

void TextureBuffer::setRepeat(GLenum repeatType, bool onS, bool onT)
{
   glBindTexture(textureType, textureID);
   if(onS)
   {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeatType);
      GL_Logger::LogError("Could not set S wrap ", glGetError());
   }
   if(onT)
   {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeatType);
      GL_Logger::LogError("Could not set T wrap ", glGetError());
   }
   glBindTexture(textureType, 0);
}

void TextureBuffer::setTextureBorderColor(const float color[4])
{
   borderColor[0] = color[0];
   borderColor[1] = color[1];
   borderColor[2] = color[2];
   borderColor[3] = color[3];
   bindBorderColor();

}
void TextureBuffer::setTextureBorderColor(glm::vec4 color)
{
   borderColor[0] = color.x;
   borderColor[1] = color.y;
   borderColor[2] = color.z;
   borderColor[3] = color.w;
   bindBorderColor();
}

void TextureBuffer::setMagnifyFiltering(GLenum filter)
{
   glBindTexture(textureType, textureID);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
   GL_Logger::LogError("Could not set magnifying filter", glGetError());
   glBindTexture(textureType, 0);
}
void TextureBuffer::setMinifyFilter(GLenum filter)
{
   glBindTexture(textureType, textureID);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
   GL_Logger::LogError("Could not set minifying filter", glGetError());
   glBindTexture(textureType, 0);
}
void TextureBuffer::bindBorderColor()
{
   glBindTexture(textureType, textureID);
   glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
   GL_Logger::LogError("Could not set texture border color", glGetError());
   glBindTexture(textureType, 0);
}

void TextureBuffer::setStoreFormat(GLint storeFmt)
{
   this->storeFmt = storeFmt;
}

void TextureBuffer::bind()
{
   glBindTexture(textureType, textureID);

}
void TextureBuffer::unbind()
{
   glBindTexture(textureType, 0);
}

GLuint TextureBuffer::getTextureID() const
{
   return textureID;
}