#ifndef __GLSL_PARSER_H__
#define __GLSL_PARSER_H__
#define GLSL_TYPE_ERROR  0x1110
#include <string>
#include <exception>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

/**
 * The GLSLParser does
 */
class GLSLParser
{
public:
   //GLSL Types
   enum GLSLType
   {
      GLSLInvalidType = -1,
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
   };

   static GLSLParser::GLSLType GLEnumToGLSLType(GLenum val);
     

   //A GLSLException is thrown when an incorrect type is passed into a program
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

   /**
    * A UniformObject represents a uniform in an OpenGL Program.
    * The object contains a name, id, and type, and can bind to the
    * program it's in.
    */
   class UniformObject
   {
      friend class Program;
      std::string name;
      GLint id;
      GLSLType type;

      void throwTypeError(std::string givenType) const;
      //Protected setID method allows Program to update the id on a rebind, without changing the type.
      //This method is protected to discourage manually setting the ID's
      void setID(int i);
   public:
      UniformObject(std::string name, GLSLType t, GLint id = -1):
      id(id),
      name(name),
      type(t)
      {

      }


      GLint getID() const;

      void bind(int i) const;
      void bind(float f) const;
      void bind(bool b) const;
      void bind(double d) const;
      void bind(const glm::vec2 & v) const;
      void bind(const glm::vec3 & v) const;
      void bind(const glm::vec4 & v) const;
      void bind(const glm::mat2 & m) const;
      void bind(const glm::mat3 & m) const;
      void bind(const glm::mat4 & m) const;

      /**
      * See if this uniform is valid;
      * @return true if valid.
      */
     bool isValid();



   };


private:

};
#endif