#ifndef __GL_STRUCTURE_H__
#define __GL_STRUCTURE_H__
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <unordered_map>
class GL_Structure
{
private:
   std::unordered_map<std::string, GLint> uniforms;
  
public:
   GL_Structure();
   /**
    * Create a copy of this structure, usually for making
    * instances. All uniforms will be set to -1 on copy.
    */
   GL_Structure(const GL_Structure & other);

   /**
    * Add an attribute to this structure
    * @param attribName name of the attribute
    */
   void addAttribute(std::string attribName);

   /**
    * Get the uniform id of the attribute in the program
    * @param  attributeName name of the struct attribute
    * @return               -1 if not found, GLint otherwise
    */
   GLint get(std::string attributeName);

   /**
    * Get all names in the strucutre
    */
   std::vector<std::string> getUniformNames();

   /**
    * Set a location for the uniform
    * @param name     the string name
    * @param location the location to be set
    * @return -1 if no uniform of that name exists
    */
   int setUniformLocation(std::string name, GLint location);


};
#endif