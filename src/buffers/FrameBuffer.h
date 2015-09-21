#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__
#include <TextureUnitManager.h>
#include <memory>
#include "FramebufferConfiguration.h"

class Framebuffer
{
public:
   Framebuffer(FramebufferConfiguration configuration);
   void deleteFramebuffer();
   void bindFrameBuffer();
   void unbindFrameBuffer();
   void enableAsTexture(GLint samplerID);
   void disableTexture();
   int getWidth();
   int getHeight();
   static void BindDefaultFramebuffer();
   bool isCompleted();
private:
   int width, height;
   GLuint framebufferID;
   GLuint renderTexture;
   std::shared_ptr<TextureUnit> texUnit;
   std::shared_ptr<FramebufferAttachment> fbAttachment;



};
#endif