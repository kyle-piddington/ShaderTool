#ifndef __ProgramManagerElementFactory_H__
#define __ProgramManagerElementFactory_H__
#include "ProgramManagerElement.h"
#include "UniformObjectController.h"
struct ProgramManagerElementFactory
{
   static std::shared_ptr<ProgramManagerElement> Create(std::shared_ptr<UniformObjectController> ctrl);

};
#endif