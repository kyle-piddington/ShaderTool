#ifndef __VEC3_ELEMENT_H__
#define __VEC3_ELEMENT_H__
#include "ProgramManagerElement.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Vec3ObjectController.h"
/**
 * An Unkown element displays a GLSL element's name,
 * but nothing else. 
 */
class Vec3Element : public ProgramManagerElement
{
public:
   Vec3Element(std::shared_ptr<Vec3ObjectController> controller);
   void render();
private:

   std::shared_ptr<Vec3ObjectController> ctrl;
};
#endif