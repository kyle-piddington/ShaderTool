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
   /**
    * Add this attachment to the framebuffer
    */
   virtual void attach() = 0;
   /**
    * Delete this attachment
    */
   virtual void cleanup() = 0;

protected:
   int width,height;

private:
   friend class FramebufferConfiguration;
   void setWidthHeight(int width, int height);

};

/**
 * NullAttachment, was used earlier, but I don't think I need it.
 */
struct NullAttachment : FramebufferAttachment
{
   void attach()
   {
   }
   void cleanup()
   {

   }
};

/**
 * Renderbuffer Attachments add a write only buffer to the Framebuffer
 * Renderbuffers are useful for stencil and depth attachments, when neither are needed
 * in a fragment shader.
 */
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

/**
 * Texture Attachments add a texture to the framebuffer.
 * Textures are useful for all attachments, when the output must be sampled later
 * in a shading pipeline.
 */
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

/**
 * The FramebufferConfiguration object provides a Framebuffer with all the attachments and information
 * it needs to successfully be created. In addition, it provides access to the textues for enabling and disabling them.
 * 
 */
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