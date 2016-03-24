#include "UniformObjectControllerFactory.h"
#include "FloatObjectController.h"
#include "Vec3ObjectController.h"
#include "TransformController.h"



std::shared_ptr<UniformObjectController> 
   UniformObjectControllerFactory::Create(std::shared_ptr<UniformObject>  obj)
{
   
   /**
    * Default names: 
    * 
    */
   switch(obj->getType())
   {
      case GLSLType::GLSLvector3:    return std::make_shared<Vec3ObjectController>(obj);
      case GLSLType::GLSLfloatingPt: return std::make_shared<FloatObjectController>(obj);
      case GLSLType::GLSLmat4      : return std::make_shared<TransformController>(obj);
      default: return std::make_shared<UniformObjectController>(obj);
   }
}

