#ifndef __TRANSFORM_MATRIX_ELEMENT_H__
#define __TRANSFORM_MATRIX_ELEMENT_H__
#include "ProgramManagerElement.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "UniformObjectController.h"
#include "Transform.h"
/**
 * An Unkown element displays a GLSL element's name,
 * but nothing else. 
 */
class TransformMatrixElement : public ProgramManagerElement
{
public:
   TransformMatrixElement(std::shared_ptr<UniformObjectController> controller);
   void render();
private:
   glm::vec3 pos;
   glm::vec3 rot;
   glm::vec3 scl;
   Transform t;
   bool dirty;
   std::shared_ptr<UniformObjectController> ctrl;
};
#endif