#ifndef __IntObjectController_h__
#define __IntObjectController_h__
#include "UniformObjectController.h"

class IntObjectController : public UniformObjectController
{
public:
   IntObjectController(std::shared_ptr<UniformObject> other):
      UniformObjectController(other),
      internalIntValue(0)
      {

      }
   IntObjectController(const IntObjectController & other):
      UniformObjectController(other),
      internalIntValue(other.internalIntValue)
      {
         UniformObjectController::bind(internalIntValue);

      }


   int getInt()
   {
      return internalIntValue;
   }

   void bind(const int value)
   {
      internalIntValue = value;
      UniformObjectController::bind(value);
   }

   void refresh()
   {
      UniformObjectController::bind(internalIntValue);
   }
private:
   int internalIntValue;

};
#endif
