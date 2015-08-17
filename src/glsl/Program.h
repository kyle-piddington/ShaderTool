#ifndef __PROGRAM_H__
#define __PROGRAM_H__ value

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <unordered_map>
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
    * Add an attribute to the program
    * @param  name the name of the attribute
    * @return      0 is success, -1 if not found
    */
   int addAttribute(std::string name);

   /**
    * Add a uniform to the program
    * @param  uniform the uniform name
    * @return         0 if success, -1 if not found
    */
   int addUniform(std::string uniform);

   /**
    * Get an attribute from the program
    * @param  name attribute name.
    * @return      the GLint of the attribute, -1 if not found.
    */
   GLint getAttribute(std::string name);

   /**
    * Get a uniform from the program
    * @param name the attribute name
    * @return the GLint of the attribute, -1 if not found.
    */
   GLint getUniform(std::string name);
   /**
    * Create the program. Call one of the above methods before doing this. Programs with no shaders attached will throw errors.
    */
   int create();

   /**
    * Check to see if all declared uniforms and attributes are bound.
    */
   bool checkBoundVariables();

   void enable();
   
   void disable();

private:
   int addShader(GLuint & whichShader, std::string shaderName, GLenum shaderType);
   
   std::string name;
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

   std::unordered_map<std::string, GLuint> attributes;
   std::unordered_map<std::string, GLint> uniforms;
   std::unordered_map<std::string, bool> boundAttributes;
   std::unordered_map<std::string, bool> boundUniforms;






};
#endif