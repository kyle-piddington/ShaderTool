#ifndef __INT_ELEMENT_H__
#define __INT_ELEMENT_H__
#include "ProgramManagerElement.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "IntObjectController.h"
/**
 * An Unkown element displays a GLSL element's name,
 * but nothing else. 
 */
class IntElement : public ProgramManagerElement
{
public:
   IntElement(std::shared_ptr<IntObjectController> controller);
   float getFloat();
   void render();
private:

   std::shared_ptr<IntObjectController> ctrl;
};
#endif