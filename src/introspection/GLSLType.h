#pragma once
#ifndef __GLSL_TYPE_H__
#define __GLSL_TYPE_H__

#include <string>
#include <exception>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

namespace GLSLType
{
    enum GLSLType
    {
        GLSLInvalidType = -99,
        GLSLinteger = GL_INT,
        GLSLfloatingPt = GL_FLOAT,
        GLSLboolean = GL_BOOL,
        GLSLvector2 = GL_FLOAT_VEC2,
        GLSLvector3 = GL_FLOAT_VEC3,
        GLSLvector4 = GL_FLOAT_VEC4,
        GLSLmat2 = GL_FLOAT_MAT2,
        GLSLmat3 = GL_FLOAT_MAT3,
        GLSLmat4 = GL_FLOAT_MAT4,
        GLSLsampler2D = GL_SAMPLER_2D,
        GLSLArray     = -1, //Some array type. (the .bind call can extract additional information once it knows it's an array)
        GLSLStruct    = -2, //Some struct type. (The .bind call can extract additional information once it knows it's a struct)
    };

    inline GLSLType GLEnumToGLSLType(GLenum val)
    {
         switch(val)
         {
            case  GL_INT:        return GLSLType::GLSLinteger;
            case  GL_FLOAT:      return GLSLType::GLSLfloatingPt;
            case  GL_BOOL:       return GLSLType::GLSLboolean;
            case  GL_FLOAT_VEC2: return GLSLType::GLSLvector2;
            case  GL_FLOAT_VEC3: return GLSLType::GLSLvector3;
            case  GL_FLOAT_VEC4: return GLSLType::GLSLvector4;
            case  GL_FLOAT_MAT2: return GLSLType::GLSLmat2;
            case  GL_FLOAT_MAT3: return GLSLType::GLSLmat3;
            case  GL_FLOAT_MAT4: return GLSLType::GLSLmat4;
            case  GL_SAMPLER_2D: return GLSLType::GLSLsampler2D;
            default:  return GLSLType::GLSLInvalidType;

         }
    }   
    inline const char* typeToString(GLSLType v) 
    {
        switch (v)
        {
          case GLSLType::GLSLInvalidType: return "Invalid Type";
          case GLSLType::GLSLinteger: return "Integer";
          case GLSLType::GLSLfloatingPt: return "Floating Point";
          case GLSLType::GLSLboolean: return "Boolean";
          case GLSLType::GLSLvector2: return "Vector2";
          case GLSLType::GLSLvector3: return "Vector3";
          case GLSLType::GLSLvector4: return "Vector4";
          case GLSLType::GLSLmat2: return "Mat2";
          case GLSLType::GLSLmat3: return "Mat3";
          case GLSLType::GLSLmat4: return "Mat4";
          case GLSLType::GLSLsampler2D: return "Sampler2d";
          case GLSLType::GLSLArray: return "Array<?>";
          case GLSLType::GLSLStruct: return "Struct<?>";

        }
    }

    class GLSLTypeException: public std::exception
    {

    public:
        GLSLTypeException(std::string src, std::string expType, std::string type):
        exception(),
        err("GLSL Type error occurred in " + src + " expected " + expType + " , got " + type)
        {

        }
        virtual const char* what() const throw()
        {
            return err.c_str();

        }
    private:
            std::string err;


    };
    class GLSLIndexException: public std::exception
    {

    public:
        GLSLIndexException(std::string err):
        exception(),
        err(err)
        {

        }
        virtual const char* what() const throw()
        {
            return err.c_str();

        }
    private:
            std::string err;


    };
}

#endif




