#ifndef __Vec3ObjectController_h__
#define __Vec3ObjectController_h__
#include "UniformObjectController.h"
#include <glm/glm.hpp>

class Vec3ObjectController : public UniformObjectController
{
public:
   Vec3ObjectController(std::shared_ptr<UniformObject> other):
      UniformObjectController(other)
      {

      }
   Vec3ObjectController(const Vec3ObjectController & other):
      UniformObjectController(other),
      internalVec3Value(other.internalVec3Value)
      {
         UniformObjectController::bind(internalVec3Value);
      }

   void bind(const glm::vec3 value)
   {
      internalVec3Value = value;
      UniformObjectController::bind(value);
   }
   void refresh()
   {
      UniformObjectController::bind(internalVec3Value);
   }
private:
   glm::vec3 internalVec3Value;

};
#endif
