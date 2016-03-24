#ifndef __FloatObjectController_h__
#define __FloatObjectController_h__
#include "UniformObjectController.h"

class FloatObjectController : public UniformObjectController
{
public:
   FloatObjectController(std::shared_ptr<UniformObject> other):
      UniformObjectController(other)
      {

      }
   FloatObjectController(const FloatObjectController & other):
      UniformObjectController(other),
      internalFloatValue(other.internalFloatValue)
      {
         UniformObjectController::bind(internalFloatValue);

      }



   void bind(const float value)
   {
      internalFloatValue = value;
      UniformObjectController::bind(value);
   }

   void refresh()
   {
      UniformObjectController::bind(internalFloatValue);
   }
private:
   float internalFloatValue;

};
#endif
