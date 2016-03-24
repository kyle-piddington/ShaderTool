#ifndef __UniformObjectControllerFactory_H__
#define __UniformObjectControllerFactory_H__
#include "UniformObjectController.h"
#include "UniformObject.h"
struct UniformObjectControllerFactory
{
   static std::shared_ptr<UniformObjectController> Create(std::shared_ptr<UniformObject> obj);
};
#endif