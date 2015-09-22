#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__
#include <TextureUnitManager.h>
#include <memory>
#include "FramebufferConfiguration.h"

class Framebuffer
{
public:
   Framebuffer();
   Framebuffer(FramebufferConfiguration configuration);
   void init(FramebufferConfiguration configuration);
   void deleteFramebuffer();
   void bindFrameBuffer();
   void unbindFrameBuffer();
   void enableTexture(std::string texName, GLint samplerID);
   void disableTexture(std::string texName);
   int getWidth();
   int getHeight();
   static void BindDefaultFramebuffer();
   bool isCompleted();

private:
   int width, height;
   FramebufferConfiguration configuration;
   GLuint framebufferID;



};
#endif