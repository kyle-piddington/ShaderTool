#include "GLSLParser.h"
#include <easyLogging++.h>
#include <glm/gtc/type_ptr.hpp>

GLSLParser::GLSLType GLSLParser::GLEnumToGLSLType(GLenum val)
{
   switch(val)
   {
      case  GL_INT:        return GLSLParser::GLSLinteger;
      case  GL_FLOAT:      return GLSLParser::GLSLfloatingPt;
      case  GL_BOOL:       return GLSLParser::GLSLboolean;
      case  GL_FLOAT_VEC2: return GLSLParser::GLSLvector2;
      case  GL_FLOAT_VEC3: return GLSLParser::GLSLvector3;
      case  GL_FLOAT_VEC4: return GLSLParser::GLSLvector4;
      case  GL_FLOAT_MAT2: return GLSLParser::GLSLmat2;
      case  GL_FLOAT_MAT3: return GLSLParser::GLSLmat3;
      case  GL_FLOAT_MAT4: return GLSLParser::GLSLmat4;
      case  GL_SAMPLER_2D: return GLSLParser::GLSLsampler2D;
      default:  return GLSLParser::GLSLInvalidType;

   }
}

inline const char* typeToString(GLSLParser::GLSLType v) 
{
    switch (v)
    {
      case GLSLParser::GLSLInvalidType: return "Invalid Type";
      case GLSLParser::GLSLinteger: return "Integer";
      case GLSLParser::GLSLfloatingPt: return "Floating Point";
      case GLSLParser::GLSLboolean: return "Boolean";
      case GLSLParser::GLSLvector2: return "Vector2";
      case GLSLParser::GLSLvector3: return "Vector3";
      case GLSLParser::GLSLvector4: return "Vector4";
      case GLSLParser::GLSLmat2: return "Mat2";
      case GLSLParser::GLSLmat3: return "Mat3";
      case GLSLParser::GLSLmat4: return "Mat4";
      case GLSLParser::GLSLsampler2D: return "Sampler2d";

    }
}

void GLSLParser::UniformObject::throwTypeError(std::string givenType) const
{
   throw GLSLTypeException(name,typeToString(type),givenType);
}
void GLSLParser::UniformObject::bind(int i) const
{

   if(type != GLSLinteger)
   {
      throwTypeError("integer");
   }
   if(id > -1)
   {
      glUniform1i(id,i);
   }
}

void GLSLParser::UniformObject::bind(float f) const
{
   if(type != GLSLfloatingPt)
   {
      throwTypeError("floating point");
   }
   if(id > -1)
   {
      glUniform1f(id,f);
   }
}

void GLSLParser::UniformObject::bind(double d) const
{
   if(type != GLSLfloatingPt)
   {
      throwTypeError("floating point");
   }
   if(id > -1)
   {
      glUniform1f(id,(float)d);
   }
}

void GLSLParser::UniformObject::bind(bool b) const
{
   if(type != GLSLboolean)
   {
      throwTypeError("boolean");
   }
   if(id > -1)
   {
      glUniform1i(id,b);
   }
}

void GLSLParser::UniformObject::bind(const glm::vec2 & v) const
{
   if(type != GLSLvector2)
   {
      throwTypeError("vector2");
   }
   if(id > -1)
   {
      glUniform2fv(id,1,glm::value_ptr(v));
   }
}

void GLSLParser::UniformObject::bind(const glm::vec3 & v) const
{
   if(type != GLSLvector3)
   {
      throwTypeError("vector3");
   }
   if(id > -1)
   {
      glUniform3fv(id,1,glm::value_ptr(v));
   }
}
void GLSLParser::UniformObject::bind(const glm::mat2 & m) const
{
   if(type != GLSLmat3)
   {
      throwTypeError("matrix2x2");
   }
   if(id > -1)
   {
      glUniformMatrix2fv(id,1,GL_FALSE,glm::value_ptr(m));
   }
}
void GLSLParser::UniformObject::bind(const glm::mat3 & m) const
{
   if(type != GLSLmat3)
   {
      throwTypeError("matrix3x3");
   }
   if(id > -1)
   {
      glUniformMatrix3fv(id,1,GL_FALSE,glm::value_ptr(m));
   }
}
void GLSLParser::UniformObject::bind(const glm::mat4 & m) const
{
   if(type != GLSLmat4)
   {
      throwTypeError("matrix4x4");
   }
   if(id > -1)
   {
      glUniformMatrix4fv(id,1,GL_FALSE,glm::value_ptr(m));
   }
}

bool GLSLParser::UniformObject::isValid()
{
   return id > -1;
}

GLint GLSLParser::UniformObject::getID() const
{
   return id;
}

void GLSLParser::UniformObject::setID(GLint id)
{
   this->id = id;
}
