#ifndef __IMGUI_TEXTURE_SELECTOR__H__
#define __IMGUI_TEXTURE_SELECTOR__H__
#include <GL/glew.h>
/**
 * Callback based texture selection.
 */
class ImguiTextureSelector
{
   ImguiTextureSelector(TextureSelectorTarget * target);
   
   void render();

private:
   const TextureSelectorTarget * cTarg;
   static std::vector<GLuint> avaliableTextures
};
#endif