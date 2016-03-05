#include "StructUniformObject.h"

StructUniformObject::StructUniformObject(std::string name):
   UniformObject(name, GLSLType::GLSLStruct, -1)
   {

   }

const UniformObject & StructUniformObject::get(std::string id) const
{
   auto unif = attributes.find(id);
   if(unif == attributes.end())
   {
      throw GLSLType::GLSLIndexException("No struct member named '" + id + "' found");
   }
   else
   {
      return *(unif->second);
   }
}

void StructUniformObject::addUniformObject(std::shared_ptr<UniformObject> obj)
{
   if(obj != nullptr)
   {
      attributes.emplace(obj->getName(),obj);
   }
}