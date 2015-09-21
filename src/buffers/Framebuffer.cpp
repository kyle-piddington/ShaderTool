
#include "Framebuffer.h"
#include <easylogging++.h>
#include <glfw/glfw3.h>
#include "GL_Logger.h"

Framebuffer::Framebuffer(FramebufferConfiguration configuration):
configuration(configuration),
width(configuration.width),
height(configuration.height),
framebufferID(0)
{
   glGenFramebuffers(1, &framebufferID);
   glBindFramebuffer(GL_FRAMEBUFFER,framebufferID);
   std::vector< std::shared_ptr<FramebufferAttachment> > attachments = configuration.getAttachments();
   for (std::vector<std::shared_ptr<FramebufferAttachment > >::iterator i = attachments.begin(); i != attachments.end(); ++i)
   {
      (*i)->attach();
   }

   if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      LOG(ERROR)<< "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
   glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void Framebuffer::deleteFramebuffer()
{
   std::vector< std::shared_ptr<FramebufferAttachment> > attachments = configuration.getAttachments();
   
   for (std::vector<std::shared_ptr<FramebufferAttachment > >::iterator i = attachments.begin(); i != attachments.end(); ++i)
   {
      (*i)->cleanup();
   }
   glDeleteFramebuffers(1,&framebufferID);
}


void Framebuffer::bindFrameBuffer()
{
   glBindFramebuffer(GL_FRAMEBUFFER,framebufferID);

}
void Framebuffer::unbindFrameBuffer()
{
   Framebuffer::BindDefaultFramebuffer();
}
void Framebuffer::enableTexture(std::string textureID, GLint samplerID)
{
   configuration.getTextureAttachment(textureID)->enableTexture(samplerID);
   
}
void Framebuffer::disableTexture(std::string textureID)
{
   configuration.getTextureAttachment(textureID)->disableTexture();
}

bool Framebuffer::isCompleted()
{
   return framebufferID != 0 && 
      glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

void Framebuffer::BindDefaultFramebuffer()
{
   glBindFramebuffer(GL_FRAMEBUFFER,0);
}
