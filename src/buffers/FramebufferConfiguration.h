#ifndef __FRAMEBUFFER_CONFIGURATION_H__
#define __FRAMEBUFFER_CONFIGURATION_H__
#include <GL/glew.h>
#include <memory>
#include <easyLogging++.h>
#include <unordered_map>
#include "TextureUnitManager.h"
/**
 * A FramebufferAttachment can either be a renderbuffer or texturebuffer
 * and are attached to the framebuffer when it is being configured
 */
class FramebufferAttachment
{
public:
   virtual void attach() = 0;
   virtual void cleanup() = 0;

protected:
   int width,height;

private:
   friend class FramebufferConfiguration;
   void setWidthHeight(int width, int height);

};

struct NullAttachment : FramebufferAttachment
{
   void attach()
   {
   }
   void cleanup()
   {

   }
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
   GLenum outputComponentType;
   GLenum outputComponentStorage;
   std::string textureName;
   TextureAttachment(std::string textureName, GLenum outputComponentType, GLenum outputComponentStorage, GLenum attachmentInfo):
   textureName(textureName),
   attachmentInfo(attachmentInfo),
   outputComponentType(outputComponentType),
   outputComponentStorage(outputComponentStorage),
   tbo(0)
   {}
   void attach();
   void cleanup();
   void enableTexture(GLuint id);
   void disableTexture();
private:
   GLuint tbo;
   std::shared_ptr<TextureUnit> texUnit;




};
class FramebufferConfiguration
{
public:

   int width, height;
   FramebufferConfiguration(int width, int height);
   FramebufferConfiguration();
   
   void addRenderbuffer(RenderbufferAttachment renderbufferInfo);
   void addTexturebuffer(TextureAttachment info);
   std::vector<std::shared_ptr<FramebufferAttachment> > getAttachments();
   std::shared_ptr<TextureAttachment> getTextureAttachment(std::string name) ;
  
   static FramebufferConfiguration DefaultFramebuffer(int w, int h);
private:
   std::unordered_map<std::string, std::shared_ptr<TextureAttachment> > fbTextures;
   std::vector<std::shared_ptr<FramebufferAttachment> > fbAttachments;
   bool isCompleted;
};
#endif