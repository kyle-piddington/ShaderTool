#ifndef __ProgramManagerElementFactory_H__
#define __ProgramManagerElementFactory_H__
#include "ProgramManagerElement.h"
#include "UniformObject.h"
struct ProgramManagerElementFactory
{
   static std::shared_ptr<ProgramManagerElement> Create(std::shared_ptr<UniformObject> object);

};
#endif