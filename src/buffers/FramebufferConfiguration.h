#ifndef __FRAMEBUFFER_CONFIGURATION_H__
#define __FRAMEBUFFER_CONFIGURATION_H__
#include <GL/glew.h>
#include <memory>
class FramebufferAttachment
{
public:
   virtual void attach() = 0;
   virtual void cleanup() = 0;
   void setWidthHeight(int width, int height);
protected:
   int width,height;

};

struct RenderbufferAttachment : FramebufferAttachment
{
   GLenum storageType;
   GLenum attachmentInfo;
   RenderbufferAttachment(GLenum storageType, GLenum attachmentInfo):
   storageType(storageType),
   attachmentInfo(attachmentInfo)
   {}
   void attach();
   void cleanup();
private:
   GLuint rbo;
};

struct TextureAttachment : FramebufferAttachment
{
   GLenum attachmentInfo;
   GLenum drawBufferInfo;
   GLenum readBufferInfo;
   TextureAttachment(
         GLenum attachmentInfo,
         GLenum drawBuffer,
         GLenum readBuffer):
   attachmentInfo(attachmentInfo),
   drawBufferInfo(drawBuffer),
   readBufferInfo(readBuffer)
   {}
   void attach();
   void cleanup();
private:
   GLuint tbo;


};
class FramebufferConfiguration
{
public:
   GLenum outputComponentType;
   GLenum outputComponentStorage;
   int width, height;
   FramebufferConfiguration(int width, int height);
   void ConfigureRenderbuffer(RenderbufferAttachment renderbufferInfo);
   void ConfigureTexturebuffer(TextureAttachment info);
   void addAttachment();
   std::shared_ptr<FramebufferAttachment> getAttachment();

   static FramebufferConfiguration DefaultRenderbuffer(int w, int h);
private:
   std::shared_ptr<FramebufferAttachment> fbAttachment;
   bool isCompleted;
};
#endif