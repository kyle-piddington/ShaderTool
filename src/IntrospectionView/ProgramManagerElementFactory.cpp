#include "ProgramManagerElementFactory.h"
#include "UnknownElement.h"
#include "Vec3Element.h"
#include "FloatElement.h"
#include "TransformMatrixElement.h"


std::shared_ptr<ProgramManagerElement> 
   ProgramManagerElementFactory::Create(std::shared_ptr<UniformObjectController>  ctrl)
{
   
   /**
    * Default names: 
    * 
    */
   switch(ctrl->getType())
   {
      case GLSLType::GLSLvector3: return std::make_shared<Vec3Element>(ctrl);
      case GLSLType::GLSLfloatingPt: return std::make_shared<FloatElement>(ctrl);
      case GLSLType::GLSLmat4      : return std::make_shared<TransformMatrixElement>(ctrl);
      default: return std::make_shared<UnkwownElement>(ctrl->getName());
   }
}

