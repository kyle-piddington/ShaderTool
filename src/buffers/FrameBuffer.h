#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__
#include <TextureUnitManager.h>
#include <memory>
#include "FramebufferConfiguration.h"

/**
 * Framebuffers allow the user to capture data from a draw pass, and sample it later
 */
class Framebuffer
{
public:
   /**
    * Create an empty framebuffer.
    */
   Framebuffer();
   /**
    * Create a framebuffer from a configuration
    */
   Framebuffer(FramebufferConfiguration configuration);
   /**
    * Initialize a framebuffer with a configuration
    * @param configuration the new configuration.
    */
   void init(FramebufferConfiguration configuration);
   /**
    * Delete the framebuffer, and all of it's attachments from the GPU
    */
   void deleteFramebuffer();
   /**
    * Bind the framebuffer object. The next read/write or Framebuffer api calls will affect this fbo.
    */
   void bindFrameBuffer();
   /**
    * Unbind the framebuffer
    */
   void unbindFrameBuffer();
   /**
    * Enable a texture attachment in the framebuffer
    * @param texName   the name of the attachment
    * @param samplerID the sampler ID attached to this attachment.
    */
   void enableTexture(std::string texName, GLint samplerID);
   /**
    * Disable a texture attachment in the framebuffer
    * @param texName the name of the attachment
    */
   void disableTexture(std::string texName);
   /**
    * Get the width of this framebuffer
    * @return the width, in px.
    */
   int getWidth(){return width;}
   /**
    * Get the height of the framebuffer
    * @return the height, in px.
    */
   int getHeight(){return height;}
   /**
    * Bind Framebuffer Object 0, effectivly unbinding all framebuffers
    */
   static void BindDefaultFramebuffer();
   /**
    * Query the GPU to see if the framebuffer is valid.
    * @return true if the Framebuffer fuffils all OpenGL contracts
    */
   bool isCompleted();

private:
   int width, height;
   FramebufferConfiguration configuration;
   GLuint framebufferID;



};
#endif