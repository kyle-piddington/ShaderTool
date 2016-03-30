#ifndef __TransformController_h__
#define __TransformController_h__
#include "UniformObjectController.h"
#include "MatrixObjectController.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include <iostream>
class TransformController : public Matrix4ObjectController
{
public:
   TransformController(std::shared_ptr<UniformObject> obj):
      Matrix4ObjectController(obj)
      {
         std::cout << "Creating transform controller" << std::endl;
      }
   TransformController(const TransformController & other):
      Matrix4ObjectController(other),
      transform(other.transform)
      {
         UniformObjectController::bind(transform.getMatrix());
      }

   void bind(const Transform & value)
   {
      transform = value;
      UniformObjectController::bind(transform.getMatrix());
   }

   void refresh()
   {
      UniformObjectController::bind(transform.getMatrix());
   }

   Transform getTransform() const
   {
      return transform;
   }

   glm::mat4 getMatrix()
   {
      return transform.getMatrix();
   }

private:
   Transform transform;

};
#endif
