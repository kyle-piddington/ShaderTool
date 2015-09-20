#include "FramebufferConfiguration.h"
FramebufferConfiguration::FramebufferConfiguration(int width, int height) : 
width(width),
height(height),
outputComponentType(GL_RGB),
outputComponentStorage(GL_UNSIGNED_BYTE)
{

}

void FramebufferConfiguration::ConfigureRenderbuffer(RenderbufferAttachment info)
{
   fbAttachment = std::shared_ptr<FramebufferAttachment>(new RenderbufferAttachment(info));
   fbAttachment->setWidthHeight(width,height);
   isCompleted = true;
}
void FramebufferConfiguration::ConfigureTexturebuffer(TextureAttachment info)
{
   fbAttachment = std::shared_ptr<FramebufferAttachment>(new TextureAttachment(info));
   isCompleted = true;
}





void RenderbufferAttachment::attach()
{
   glGenRenderbuffers(1, &rbo);
   glBindRenderbuffer(GL_RENDERBUFFER, rbo);
   glRenderbufferStorage(GL_RENDERBUFFER, storageType, width, height);
   glBindRenderbuffer(GL_RENDERBUFFER, 0);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentInfo, GL_RENDERBUFFER, rbo);
}

void FramebufferAttachment::setWidthHeight(int w, int h)
{
   this->width = w;
   this->height = h;
}

void RenderbufferAttachment::cleanup()
{
   glDeleteRenderbuffers(1, &rbo);
}



FramebufferConfiguration FramebufferConfiguration::DefaultRenderbuffer(int w, int h)
{
   FramebufferConfiguration config(w,h);
   RenderbufferAttachment attachment(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
   config.ConfigureRenderbuffer(attachment);
   return config;
}