#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__
#include <TextureUnitManager.h>
#include <memory>
class Framebuffer
{
public:
   Framebuffer(int w, int h);
   void deleteFramebuffer();
   void bindFrameBuffer();
   void unbindFrameBuffer();
   void enableAsTexture(GLint samplerID);
   void disableTexture();
   int getWidth();
   int getHeight();
   static void BindDefaultFramebuffer();

private:
   int width, height;
   GLuint framebufferID;
   GLuint renderTexture;
   GLuint rbo;
   std::shared_ptr<TextureUnit> texUnit;


};
#endif