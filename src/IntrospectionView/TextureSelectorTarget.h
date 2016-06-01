#ifndef __TEXTURE_SELECTOR_TARGET_H__
#define __TEXTURE_SELECTOR_TARGET_H__
class TextureSelectorTarget
{
   virtual void textureSelectedCallback(GLuint data, bool isValidData) = 0;
};
#endif