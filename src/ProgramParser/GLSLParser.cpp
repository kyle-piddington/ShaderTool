#include "GLSLParser.h"
#include <easyLogging++.h>
#include <glm/gtc/type_ptr.hpp>

void GLSLParser::UniformObject::bind(int i)
{

   if(type != GLSLinteger)
   {
      throw GLSLTypeException(name, "integer");
   }
   if(id > -1)
   {
      glUniform1i(id,i);
   }
}

void GLSLParser::UniformObject::bind(float f)
{
   if(type != GLSLfloatingPt)
   {
      throw GLSLTypeException(name, "floating point");
   }
   if(id > -1)
   {
      glUniform1f(id,f);
   }
}

void GLSLParser::UniformObject::bind(bool b)
{
   if(type != GLSLboolean)
   {
      throw GLSLTypeException(name, "boolean");
   }
   if(id > -1)
   {
      glUniform1i(id,b);
   }
}

void GLSLParser::UniformObject::bind(const glm::vec2 & v)
{
   if(type != GLSLvector2)
   {
      throw GLSLTypeException(name, "vector2");
   }
   if(id > -1)
   {
      glUniform2fv(id,1,glm::value_ptr(v));
   }
}


