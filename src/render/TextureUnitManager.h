#ifndef __TEXTURE_UNIT_MANAGER_H__
#define __TEXTURE_UNIT_MANAGER_H__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>

struct TextureUnit;
class Compare;
class TextureUnitManager
{
public:
   friend struct TextureUnit;
   static void init();
   static TextureUnit requestTextureUnit();

private:

   static bool initted;
   static std::priority_queue<TextureUnit, std::vector<TextureUnit>, Compare> unitQueue;

};



struct TextureUnit
{
   const int getTexUnit();
   const GLenum getGlUnit();
   void release();
   TextureUnit(const TextureUnit  & other):
      texUnit(other.texUnit),
      glUnit(other.glUnit),
      active(other.active){}
   

private:
   bool active;
   int texUnit;
   GLenum glUnit;

    TextureUnit(int texIdx, GLenum glUnit):
     texUnit(texIdx),
      glUnit(glUnit),
      active(true){}

    friend class TextureUnitManager;
    friend class Compare;
};

class Compare
{

public:
    bool operator() (const TextureUnit & a , const TextureUnit & b) const
    {
        return a.texUnit > b.texUnit;
    }
};

#endif