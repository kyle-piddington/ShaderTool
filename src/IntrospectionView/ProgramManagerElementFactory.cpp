#include "ProgramManagerElementFactory.h"
#include "UnknownElement.h"
#include "Vec3Element.h"
#include "FloatElement.h"
#include "TransformMatrixElement.h"
#include "TransformController.h"

std::shared_ptr<ProgramManagerElement> 
   ProgramManagerElementFactory::Create(std::shared_ptr<UniformObjectController>  ctrl)
{
   
   /**
    * Default names: 
    * 
    */
   switch(ctrl->getType())
   {
      //case GLSLType::GLSLvector3: return std::make_shared<Vec3Element>(ctrl);
      //case GLSLType::GLSLfloatingPt: return std::make_shared<FloatElement>(ctrl);
      /** I'm so sorry about htis :( I can't vigure out a better design.*/
      case GLSLType::GLSLmat4      : return std::make_shared<TransformMatrixElement>(std::static_pointer_cast<TransformController>(ctrl));
      default: return std::make_shared<UnkwownElement>(ctrl->getName());
   }
}

