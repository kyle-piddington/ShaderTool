#include "FramebufferConfiguration.h"
#include "GL_Logger.h"
FramebufferConfiguration::FramebufferConfiguration(int width, int height) : 
width(width),
height(height)
{

}

void FramebufferConfiguration::addRenderbuffer(RenderbufferAttachment info)
{
   std::shared_ptr<FramebufferAttachment> fbAttachment = std::shared_ptr<FramebufferAttachment>(new RenderbufferAttachment(info));
   fbAttachment->setWidthHeight(width,height);
   fbAttachments.push_back(fbAttachment);
   
}

void FramebufferConfiguration::addTexturebuffer(TextureAttachment info)
{
   std::shared_ptr<TextureAttachment> texAtch = std::shared_ptr<TextureAttachment>(new TextureAttachment(info));
   std::shared_ptr<FramebufferAttachment> fbAttachment = texAtch;
   fbAttachment->setWidthHeight(width,height);
   fbAttachments.push_back(fbAttachment);
   fbTextures[texAtch->textureName] = texAtch;

}

std::vector<std::shared_ptr<FramebufferAttachment> > FramebufferConfiguration::getAttachments()
{
   return fbAttachments;
}

FramebufferConfiguration FramebufferConfiguration::DefaultFramebuffer(int w, int h)
{
   FramebufferConfiguration config(w,h);
   RenderbufferAttachment attachment(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
   config.addRenderbuffer(attachment);
   TextureAttachment tbuffer("color", GL_RGB,GL_UNSIGNED_BYTE,GL_COLOR_ATTACHMENT0);
   config.addTexturebuffer(tbuffer);
   return config;
}

//@TODO, better error handling
std::shared_ptr<TextureAttachment> FramebufferConfiguration::getTextureAttachment(std::string name)
{
   return fbTextures[name];
}


void FramebufferAttachment::setWidthHeight(int w, int h)
{
   this->width = w;
   this->height = h;
}



void RenderbufferAttachment::attach()
{
   glGenRenderbuffers(1, &rbo);
   glBindRenderbuffer(GL_RENDERBUFFER, rbo);
   glRenderbufferStorage(GL_RENDERBUFFER, storageType, width, height);
   glBindRenderbuffer(GL_RENDERBUFFER, 0);
   glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentInfo, GL_RENDERBUFFER, rbo);
}


void RenderbufferAttachment::cleanup()
{
   glDeleteRenderbuffers(1, &rbo);
}

//@TODO, learn how to use texture attachments to framebuffers
void TextureAttachment::attach()
{
   if(tbo == 0)
   {
      glGenTextures(1,&tbo);
      glBindTexture(GL_TEXTURE_2D, tbo);
      GL_Logger::LogError("Could activate texture at tbo id " + std::to_string(tbo), glGetError());
 
      glTexImage2D(GL_TEXTURE_2D, 0, outputComponentType,
                width, height, 0, outputComponentType, 
                outputComponentStorage, NULL);
      GL_Logger::LogError("Could set texture data in texturebuffer " + std::to_string(tbo), glGetError());
 
      //Generate a texture to write this FBO to.
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);

      //Add the texture to the framebuffer
      glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentInfo, GL_TEXTURE_2D, tbo, 0);

   }

}

void TextureAttachment::enableTexture(GLuint samplerID)
{
   if(texUnit == nullptr)
   {
      texUnit = std::make_shared<TextureUnit>(TextureUnitManager::requestTextureUnit());
      glActiveTexture(texUnit->getGlUnit());
      GL_Logger::LogError("Could not activate framebuffer texture", glGetError());
   }
   glBindTexture(GL_TEXTURE_2D,tbo);
   GL_Logger::LogError("Could activate texture at tbo id " + std::to_string(tbo), glGetError());
 
   glUniform1i(samplerID, texUnit->getTexUnit());

}

void TextureAttachment::disableTexture()
{
   if(texUnit != nullptr)
   {
      texUnit->release();
   }
   glBindTexture(GL_TEXTURE_2D,0);
   texUnit = nullptr;
}

void TextureAttachment::cleanup()
{
   if(texUnit != nullptr)
   {
      texUnit->release();
      texUnit = nullptr;
   }
   glDeleteTextures(1,&tbo);
}


 

