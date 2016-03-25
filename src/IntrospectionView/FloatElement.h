#ifndef __FLOAT_ELEMENT_H__
#define __FLOAT_ELEMENT_H__
#include "ProgramManagerElement.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "FloatObjectController.h"
/**
 * An Unkown element displays a GLSL element's name,
 * but nothing else. 
 */
class FloatElement : public ProgramManagerElement
{
public:
   FloatElement(std::shared_ptr<FloatObjectController> controller);
   float getFloat();
   void render();
private:

   std::shared_ptr<FloatObjectController> ctrl;
};
#endif