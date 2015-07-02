#ifndef __TEXTURE_UNIT_MANAGER_H__
#define __TEXTURE_UNIT_MANAGER_H__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

struct TextureUnit;

class TextureUnitManager
{
public:
   friend struct TextureUnit;
   static void init();
   static TextureUnit requestTextureUnit();
  
private:
   static int texIdx;
   static bool initted;
   static std::vector<TextureUnit> unitQueue;

};



struct TextureUnit
{

   const int texUnit;
   const GLenum glUnit;
   void release();
private:
    TextureUnit(int texIdx, GLenum glUnit):
     texUnit(texIdx),
      glUnit(glUnit){}
    friend class TextureUnitManager;
};

#endif