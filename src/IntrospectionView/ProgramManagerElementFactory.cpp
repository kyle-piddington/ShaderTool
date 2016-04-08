#include "ProgramManagerElementFactory.h"
#include "UnknownElement.h"
#include "Vec3Element.h"
#include "FloatElement.h"
#include "IntElement.h"
#include "TransformMatrixElement.h"
#include "TransformController.h"
#include "Vec3ObjectController.h"
#include "FloatObjectController.h"
#include "IntObjectController.h"

std::shared_ptr<ProgramManagerElement>
   ProgramManagerElementFactory::Create(std::shared_ptr<UniformObjectController>  ctrl)
{

   /**
    * Default names:
    *
    */
   switch(ctrl->getType())
   {
      case GLSLType::GLSLvector3:
        return std::make_shared<Vec3Element>(std::static_pointer_cast<Vec3ObjectController>(ctrl));
      case GLSLType::GLSLfloatingPt:
        return std::make_shared<FloatElement>(std::static_pointer_cast<FloatObjectController>(ctrl));
      case GLSLType::GLSLmat4:
        return std::make_shared<TransformMatrixElement>(std::static_pointer_cast<TransformController>(ctrl));
      case GLSLType::GLSLinteger:
        return std::make_shared<IntElement>(std::static_pointer_cast<IntObjectController>(ctrl));
      default: return std::make_shared<UnkwownElement>(ctrl->getName());
   }
}

