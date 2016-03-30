#ifndef __MATRIX_OBJECT_CONTROLLER_H__
#define __MATRIX_OBJECT_CONTROLLER_H__
#include "UniformObjectController.h"
/**
 * An exposing interface for underlying matrix types.
 */
class Matrix4ObjectController : public UniformObjectController
{
public:
   Matrix4ObjectController(std::shared_ptr<UniformObject> obj):
      UniformObjectController(obj)
      {

      }
   Matrix4ObjectController(const Matrix4ObjectController & other):
      UniformObjectController(other)
      {
         
      }

   virtual ~Matrix4ObjectController(){}

   virtual glm::mat4 getMatrix() = 0;   


};
#endif