  #ifndef __PROGRAM_H__
#define __PROGRAM_H__

//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <iostream>
#include "GL_Structure.h"
#include "Shader.h"
#include <unordered_map>
#include "GLSLParser.h"
namespace ProgramStatus
{
  enum CreateStatus
     {
        OK = 0,
        NOCHANGE = 1,
        COMPILE_ERR= - 1,
        NOT_ENOUGH_SHADERS_ERR= - 2,
        LINK_ERR  = -3
     };
}

/**
 * A program represents the current state of a GLSL shader program. The program class
 * provides ways to query, access, and set parameters of a GLSL shader program.
 * The program class also handles compiling a set of shaders in order to for ma complete program.
 */
class Program
{
public:

   struct UniformArrayInfo
   {
      std::string baseName;
      std::vector<GLint> locations;
      GLint operator[](std::size_t idx){return locations[idx];}
      size_t size() const {return locations.size();}
      bool isValid;
   };
   struct UniformStructArrayInfo
   {
      std::string baseName;
      std::vector<GL_Structure> structs;
      GL_Structure const &operator[](std::size_t idx) const{return structs[idx];}
      size_t size() const {return structs.size();}
      bool isValid;

   };


   /**
    * Initialize the program object
    */
   Program(std::string name);
   /**
    * Remove the program object
    */
   ~Program();
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
    * See if a program has a uniform, without adding it to the program.
    * @param
    * @return         >0  if exists, -1 otherwise.
    */
   bool hasUniform(std::string uniform);
  
   /**
    * See if the programmer has added a unifrom
    * @param  uniform uniform to check
    * @return         true if "addUniform" has been called
    */
   bool hasAddedUniform(std::string uniform);
  
   /**
    * Add a GLStruct uniform to the program
    * @param  name   name of the instance in the program
    * @param  struct struct to bind the instance to
    * @return        0 if OK, -1 otherwise
    */
   int addUniformStruct(std::string name, GL_Structure  glStruct);

   /**
    * Add a uniform array to the program
    * @param arr the array base name
    * @param len the maximum length
    */
    int addUniformArray(std::string base, int len);

    /**
     * Add a uniform array of structs to the program
     * @param arr the array base name
     * @param len the maximum length
     * @param struct the structure
     * @return 0 if OK
     */
    int addStructArray(std::string arrName, int len, GL_Structure  glStruct);

    /**
     * Get an array from the program
     * @param  name name of the array
     * @return      reference to the array
     */
    const UniformArrayInfo  & getArray(std::string name);

    /**
     * Get an array of structs from the program
     * @param  name the name of the array
     * @return      reference to the array
     */
    const UniformStructArrayInfo  & getStructArray(std::string name);

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
   GLSLParser::UniformObject getUniform(std::string name);


   /**
    * Get a uniform from the program
    * @param name the attribute name
    * @return the GLint of the attribute, -1 if not found.
    */
   GL_Structure getUniformStruct(std::string name);

   /**
    * Create the program. Call one of the above methods before doing this. Programs with no shaders attached will throw errors.
    */
   int create();

   /**
    * Check to see if all declared uniforms and attributes are bound.
    */
   bool checkBoundVariables();

   /**
    * Enable the program as the active GLFW program
    */
   void enable();

   /**
    * Disable this program as the active GLFW program.
    * (This function only needs to be called for the last program, due to how the opengl state machine works)
    */
   void disable();

   /**
    * Chech the program's shaders to see if any changes have occurred.
    * @return true if the program should recompile
    */
   bool shouldProgramRecompile();

   /**
    * Check to see if the program exists on the GPU (Has been created once).
    * After an initial compile, this function will return true for the remainder of the program's lifetime
    * @return true if the program has compiled at least once.
    */
   bool isCreated();
private:


  /**
   * ProgCreationInfo is a tuple containing data regarding a program being compiled.
   * The program integer will be nonzero if the program succeeded at compiling it's shaders
   * the status may indicate a link failure. Appropriate action will be taken in create() to deal with these errors
   */
  struct ProgCreationInfo
   {
      ProgramStatus::CreateStatus status;
      GLuint program;
   };


   /**
    * Addd a shader to the program
    * @param whichShader the Shader program to add
    * @param shaderName the name of the shader, for print out purposes
    * @param shaderType Indicates if this shader is a vertex, fragment, geometry, tessalation, or other.
    * @return 0 if OK, -1 otherwise.
    */
   int addShader(std::shared_ptr<Shader> & whichShader, std::string shaderName, GLenum shaderType);

   /**
    * Compile all shaders return 0 if ok, -1 otherwise.

    */
   int compileAllShaders();

   /**
    * Retrieve the type of a uniform in the program.
    */
   GLSLParser::GLSLType getUniformType(GLuint id);

   /**
    * Create and link a shader program.
    * @return a tuple containing the program's ID, and the status of the program.
    */
   ProgCreationInfo createProgram();

   std::string name;
   bool created;

   GLuint shaderProgram;

   std::shared_ptr<Shader> vertShader;
   std::shared_ptr<Shader> fragShader;
   std::shared_ptr<Shader> geomShader;
   std::shared_ptr<Shader> tessalationShader;

   std::unordered_map<std::string, GLuint> attributes;
   std::unordered_map<std::string, GLSLParser::UniformObject> uniforms;
   std::unordered_map<std::string, GL_Structure> uniformStructs;

   std::unordered_map<std::string, bool> boundAttributes;
   std::unordered_map<std::string, bool> boundUniforms;

   std::unordered_map<std::string, UniformArrayInfo> arrays;
   std::unordered_map<std::string, UniformStructArrayInfo> structArrays;


   UniformArrayInfo emptyUniformArray;
   UniformStructArrayInfo emptyStructUniformArray;


};
#endif