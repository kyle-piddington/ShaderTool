#ifndef __TEXTURE_BUFFER_H__
#define __TEXTURE_BUFFER_H__
#include <glm/glm.hpp>
#include <GL/glew.h>

class TextureBuffer
{
public:
   /**
    * Create a texture. Default options for textures are
    *    TextureType: GL_TEXTURE1/2D. No 3d support (YET)
    *    S-Wrap: True
    *    T-Wrap: True
    *    Generate Mipmaps: True
    *    Magnification Filter: GL_LINEAR
    *    Minification Filter: GL_LINEAR_MIPMAP_LINEAR
    *    Store format: GL_RGB
    *    Load Format: GL_RGB
    *    Generate Mipmaps: True
    *    Border color: 1.0, 0.0, 1.0, 1.0
    */
   TextureBuffer(GLenum textureType);
   ~TextureBuffer();
   /**
    * Set the texture data
    * @param  img             Pointer to the texture data
    * @param  width           width of the data
    * @param  height          height of the data
    * @param  dataFmt         data format (GL_RGB/RGBA)
    * @param  dataType        Type of the data. GL_UNSIGNED_BYTE
    * @param  generateMipMaps Generate a mipmap of this texture (Default true)
    * @return                 0 if OK.
    */
   int setData(const void * img, int width, int height, GLint dataFmt, GLenum dataType, bool generateMipMaps = true);

   /**
    * Set the repeat direction
    * @param repeatType The type of repeat
    * @param onS        If the reapeat should be applied on S
    * @param onT        If the repeat should be applied on T
    */
   void setRepeat(GLenum repeatType, bool onS = true, bool onT = true);
   
   /**
    * Set the border color of the texture
    */
   void setTextureBorderColor(const float color[4]);
   /**
    * Same as above, but with a vec4 instead of a float array
    * @param color [description]
    */
   void setTextureBorderColor(glm::vec4 color);
   /**
    * Set the magnification texture filter scheme
    * @param filter OpenGL filter to use.
    */
   void setMagnifyFiltering(GLenum filter);
   
   /**
    * Set the minification texture strategy
    * @param filter The opengl filter to use
    */
   void setMinifyFilter(GLenum filter);
  
    void setStoreFormat(GLint storeFmt);

   /**
    * Bind the texture
    */
   void bind();
   /**
    * Unbind the texture
    */
   void unbind();

   GLuint getTextureID() const;

private:
   void bindBorderColor();
   float borderColor[4];
   GLuint textureID;
   GLenum SWrapType;
   GLenum TWrapType;
   GLenum magnifyFilter;
   GLenum minifyFilter;
   const GLenum textureType;
   GLint storeFmt;

};

#endif