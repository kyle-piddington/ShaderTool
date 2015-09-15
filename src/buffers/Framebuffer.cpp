
#include "Framebuffer.h"
#include <easylogging++.h>
#include <glfw/glfw3.h>
#include "GL_Logger.h"
Framebuffer::Framebuffer(int width, int height):
width(width),
height(height),
texUnit(nullptr)
{
   glGenFramebuffers(1, &framebufferID);
   glBindFramebuffer(GL_FRAMEBUFFER,framebufferID);
   glGenTextures(1,&renderTexture);
   glBindTexture(GL_TEXTURE_2D, renderTexture);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

   //Generate a texture to write this FBO to.
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glBindTexture(GL_TEXTURE_2D, 0);

   //Add the texture to the framebuffer
   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);

   //Generate a Renderbuffer for this FBO. Add a switch here to generate a texture instead!
   glGenRenderbuffers(1, &rbo);
   glBindRenderbuffer(GL_RENDERBUFFER, rbo);
   glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
   glBindRenderbuffer(GL_RENDERBUFFER, 0);

   //Add the renderbuffer to the framebuffer
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

   if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      LOG(ERROR)<< "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
   glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Framebuffer::deleteFramebuffer()
{
   glDeleteTextures(1,&renderTexture);
   glDeleteRenderbuffers(1,&rbo);
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
void Framebuffer::enableAsTexture(GLint samplerID)
{
   texUnit = std::make_shared<TextureUnit>(TextureUnitManager::requestTextureUnit());
   glActiveTexture(texUnit->getGlUnit());
   GL_Logger::LogError("Could not activate fbo texture", glGetError());
   glBindTexture(GL_TEXTURE_2D,renderTexture);
   glUniform1i(samplerID, texUnit->getTexUnit());
   GL_Logger::LogError("Could not set fbo texture uniform", glGetError());
}
void Framebuffer::disableTexture()
{
   if(texUnit != nullptr)
      texUnit->release();
   glActiveTexture(GL_TEXTURE0);
   texUnit = nullptr;

}

void Framebuffer::BindDefaultFramebuffer()
{
   glBindFramebuffer(GL_FRAMEBUFFER,0);
}
