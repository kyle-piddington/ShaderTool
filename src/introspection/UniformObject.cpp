#include "UniformObject.h"
#include "GLSLType.h"
#include <glm/gtc/type_ptr.hpp>


UniformObject UniformObject::InvalidObject = UniformObject("Invalid",GLSLType::GLSLInvalidType,-1);

void UniformObject::throwTypeError(std::string givenType) const
{
   throw GLSLType::GLSLTypeException(name,GLSLType::typeToString(type),givenType);
}

void UniformObject::bind(int i) const
{

   if(type != GLSLType::GLSLinteger)
   {
      throwTypeError("integer");
   }
   if(id > -1)
   {
      glUniform1i(id,i);
   }
}

void UniformObject::bind(float f) const
{
   if(type != GLSLType::GLSLfloatingPt)
   {
      throwTypeError("floating point");
   }
   if(id > -1)
   {
      glUniform1f(id,f);
   }
}

void UniformObject::bind(double d) const
{
   if(type != GLSLType::GLSLfloatingPt)
   {
      throwTypeError("floating point");
   }
   if(id > -1)
   {
      glUniform1f(id,(float)d);
   }
}

void UniformObject::bind(bool b) const
{
   if(type != GLSLType::GLSLboolean)
   {
      throwTypeError("boolean");
   }
   if(id > -1)
   {
      glUniform1i(id,b);
   }
}

void UniformObject::bind(const glm::vec2 & v) const
{
   if(type != GLSLType::GLSLvector2)
   {
      throwTypeError("vector2");
   }
   if(id > -1)
   {
      glUniform2fv(id,1,glm::value_ptr(v));
   }
}

void UniformObject::bind(const glm::vec3 & v) const
{
   if(type != GLSLType::GLSLvector3)
   {
      throwTypeError("vector3");
   }
   if(id > -1)
   {
      glUniform3fv(id,1,glm::value_ptr(v));
   }
}
void UniformObject::bind(const glm::mat2 & m) const
{
   if(type != GLSLType::GLSLmat3)
   {
      throwTypeError("matrix2x2");
   }
   if(id > -1)
   {
      glUniformMatrix2fv(id,1,GL_FALSE,glm::value_ptr(m));
   }
}

void UniformObject::bind(const glm::mat3 & m) const
{
   if(type != GLSLType::GLSLmat3)
   {
      throwTypeError("matrix3x3");
   }
   if(id > -1)
   {
      glUniformMatrix3fv(id,1,GL_FALSE,glm::value_ptr(m));
   }
}

void UniformObject::bind(const glm::mat4 & m) const
{
   if(type != GLSLType::GLSLmat4)
   {
      throwTypeError("matrix4x4");
   }
   if(id > -1)
   {
      glUniformMatrix4fv(id,1,GL_FALSE,glm::value_ptr(m));
   }
}

bool UniformObject::isValid() const
{
   return id > -1;
}

GLint UniformObject::getID() const
{
   return id;
}

void UniformObject::setID(GLint id)
{
   this->id = id;
}

bool UniformObject::isArray() const
{
   return this->type == GLSLType::GLSLArray;
}
bool UniformObject::isStruct() const
{
   return this->type == GLSLType::GLSLStruct;
}