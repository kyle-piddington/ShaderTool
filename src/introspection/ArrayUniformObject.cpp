#include "ArrayUniformObject.h"

ArrayUniformObject::ArrayUniformObject(std::string name,
                                       const std::vector < std::shared_ptr < UniformObject > >
                                          & arrayObj):
   UniformObject(name,GLSLType::GLSLArray),
   elements(arrayObj)
{

}

const UniformObject & ArrayUniformObject::get(int idx) const
{
   if(idx >= 0 && idx < elements.size())
   {
      return *elements[idx];
   }
   else
   {
      throw GLSLType::GLSLIndexException("Index out of range");
   }
}

int ArrayUniformObject::size() const
{
   return elements.size();
}
