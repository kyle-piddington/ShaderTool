#include "ProgramManagerElementFactory.h"
#include "UnknownElement.h"
#include "Vec3Element.h"
#include "FloatElement.h"


std::shared_ptr<ProgramManagerElement> 
   ProgramManagerElementFactory::Create(std::shared_ptr<UniformObject>  object)
{
   
   /**
    * Default names: 
    * 
    */
   switch(object->getType())
   {
      case GLSLType::GLSLvector3: return std::make_shared<Vec3Element>(object);
      case GLSLType::GLSLfloatingPt: return std::make_shared<FloatElement>(object);
      default: return std::make_shared<UnkwownElement>(object->getName());
   }
}

