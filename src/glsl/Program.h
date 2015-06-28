#ifndef __PROGRAM_H__
#define __PROGRAM_H__ value

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


class Program
{
public:
   /**
    * Initialize the program object
    */
   Program(std::string name);

   /**
    * Add a vertex buffer to the program
    * @param shaderSrc String of the program source
    * @return 0 if no errors
    */
   int addVertexShader(std::string shaderSrc);
   /**
    * Add a fragment shader to the program
    * @param shaderSrc std::String pointing towards the program source
    * @return 0 if no errors
    */
   int addFragmentShader(std::string shaderSrc);
   /**
    * Add a geometry shader to the program
    * @param shaderSrc std::String pointing to the geometry shader
    * @return 0 if no errors
    */
   int addGeometryShader(std::string shaderSrc);
   /**
    * Add a tessalation shader to the program
    * @param shaderSrc std::String pointing to the tessalation shader
    * @return 0 if no errors
    */
   int addTessalationShader(std::string shaderSrc);

   /**
    * Create the program. Call one of the above methods before doing this. Programs with no shaders attached will throw errors.
    */
   int create();

   void enable();
   void disable();

private:
   std::string name;
   int addShader(GLuint & whichShader, std::string shaderName, GLenum shaderType);
   bool created;
   GLuint shaderProgram;

   GLuint vertShader;
   std::string vertShaderName;

   GLuint fragShader;
   std::string fragShaderName;

   GLuint geomShader;
   std::string geomShaderName;

   GLuint tessalationShader;
   std::string tessShaderName;


};
#endif