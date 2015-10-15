#ifndef __GLSL_PARSER_H__
#define __GLSL_PARSER_H__
#define GLSL_TYPE_ERROR  0x1110
#include <string>
#include <exception>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

/**
 * The GLSLParser c
 */
class GLSLParser
{
public:
   //GLSL Types
   enum GLSLType
   {
      GLSLinteger,
      GLSLfloatingPt,
      GLSLboolean,
      GLSLvector2,
      GLSLvector3,
      GLSLvector4,
      GLSLiVector1,
      GLSLiVector2,
      GLSLiVector3,
      GLSLiVector4,
      GLSLmat2,
      GLSLmat3,
      GLSLmat4,
      GLSLsampler2D,
      GLSLstructure,
      GLSLarray
   };


   //A GLSLException is thrown when an incorrect type is passed into a program

   class GLSLTypeException: public std::exception
   {
     public:
        GLSLTypeException(std::string src, std::string type):
         exception(),
         err("GLSL Type error occurred in " + src + ", expected " + type)
        {

        }
        virtual const char* what() const throw()
        {
          return err.c_str();
        }
   private:
      std::string err;
      
   };

   /**
    * A UniformObject represents a 
    */
   class UniformObject
   {
     
      std::string name;
      GLint id;
      GLSLType type;
      
      void throwTypeError();

   public:
      UniformObject(std::string name, GLSLType t):
      id(-1),
      name(name),
      type(t)
      {

      }
      void bind(int i);
      void bind(float f);
      void bind(bool b);
      void bind(const glm::vec2 & v);


   };


private:

};
#endif