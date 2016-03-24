#include "UniformObjectController.h"
#include <iostream>

UniformObjectController::UniformObjectController(std::shared_ptr<UniformObject> obj):
   object(obj)
{
  std::cout << "Creating controller for " << getName() << std::endl;
   assert(obj->isValid());
}
UniformObjectController::~UniformObjectController()
{

}
UniformObjectController::UniformObjectController(const UniformObjectController & other):
   object(other.object)
{

  assert(object->isValid());
  
}



bool UniformObjectController:: operator== (const UniformObjectController & other) const
{
   return other.getName() == this->getName() &&
             other.getType() == this->getType();
}

const std::string & UniformObjectController::getName() const
{
   return object->getName();
}
GLSLType::GLSLType UniformObjectController::getType() const
{
   return object->getType();
}

