
#include "Framebuffer.h"
#include <easylogging++.h>
#include <glfw/glfw3.h>
#include "GL_Logger.h"

Framebuffer::Framebuffer(FramebufferConfiguration configuration):
width(configuration.width),
height(configuration.height),
texUnit(nullptr)
{
   glGenFramebuffers(1, &framebufferID);
   glBindFramebuffer(GL_FRAMEBUFFER,framebufferID);
   glGenTextures(1,&renderTexture);
   glBindTexture(GL_TEXTURE_2D, renderTexture);

   glTexImage2D(GL_TEXTURE_2D, 0, configuration.outputComponentType,
                width, height, 0, configuration.outputComponentType, 
                configuration.outputComponentStorage, NULL);

   //Generate a texture to write this FBO to.
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glBindTexture(GL_TEXTURE_2D, 0);

   //Add the texture to the framebuffer
   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);

   //Attach the bounded config
   fbAttachment = configuration.getAttachment();
   fbAttachment->attach();
   
   
   if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      LOG(ERROR)<< "ERROR::FRAMEBUFFER:: Framebuffer is not complete!";
   glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Framebuffer::deleteFramebuffer()
{
   fbAttachment->cleanup();
   glDeleteTextures(1,&renderTexture);
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
   if(texUnit == nullptr)
   {
      texUnit = std::make_shared<TextureUnit>(TextureUnitManager::requestTextureUnit());
      glActiveTexture(texUnit->getGlUnit());
      GL_Logger::LogError("Could not activate fbo texture", glGetError());
   }
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
