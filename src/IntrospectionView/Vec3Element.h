#ifndef __VEC3_ELEMENT_H__
#define __VEC3_ELEMENT_H__
#include "ProgramManagerElement.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "UniformObjectController.h"
/**
 * An Unkown element displays a GLSL element's name,
 * but nothing else. 
 */
class Vec3Element : public ProgramManagerElement
{
public:
   Vec3Element(std::shared_ptr<UniformObjectController> controller);
   void render();
private:
   glm::vec3 vector;
   std::shared_ptr<UniformObjectController> ctrl;
};
#endif