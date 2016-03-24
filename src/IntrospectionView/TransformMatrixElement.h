#ifndef __TRANSFORM_MATRIX_ELEMENT_H__
#define __TRANSFORM_MATRIX_ELEMENT_H__
#include "ProgramManagerElement.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "UniformObjectController.h"
#include "TransformController.h"
/**
 * An Unkown element displays a GLSL element's name,
 * but nothing else. 
 */
class TransformMatrixElement : public ProgramManagerElement
{
public:
   TransformMatrixElement(std::shared_ptr<TransformController> controller);
   void render();
private:
   std::shared_ptr<TransformController> ctrl;
   glm::vec3 pos, rot, scl;
   bool dirty;
};
#endif