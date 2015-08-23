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
    * Add an attribute to this structure
    * @param attribName name of the attribute
    */
   void addAttribute(std::string attribName);

   /**
    * Get the uniform id of the attribute in the program
    * @param  attributeName name of the struct attribute
    * @return               -1 if not found, GLint otherwise
    */
   const GLint get(std::string attributeName) const;

   /**
    * Get all names in the strucutre
    */
   std::vector<std::string> getUniformNames();

   /**
    * Same as 'get', but with operator syntax
    * @param  idx string idx
    * @return     GLint if exists
    */
   const GLint operator[] (std::string idx) const {return get(idx);}

   /**
    * Set a location for the uniform
    * @param name     the string name
    * @param location the location to be set
    * @return -1 if no uniform of that name exists
    */
   int setUniformLocation(std::string name, GLint location);


};
#endif