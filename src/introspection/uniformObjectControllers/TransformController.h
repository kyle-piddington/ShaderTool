#ifndef __TransformController_h__
#define __TransformController_h__
#include "UniformObjectController.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include <iostream>
class TransformController : public UniformObjectController
{
public:
   TransformController(std::shared_ptr<UniformObject> obj):
      UniformObjectController(obj)
      {
         std::cout << "Creating transform controller" << std::endl;
      }
   TransformController(const TransformController & other):
      UniformObjectController(other),
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

private:
   Transform transform;

};
#endif
