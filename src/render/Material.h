#ifndef __MATERIAL_H__
#define __MATERIAL_H__ 
#include <glm/glm.hpp>
#include <glfw/glfw3.h>
#include "GL_Structure.h"
struct Material
{
   Material(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shininess);
   void bind(GLint ambLoc, GLint diffLoc, GLint specLoc, GLint shininessLoc);
   static GL_Structure getStruct();
   glm::vec3 ambient;
   glm::vec3 diffuse;
   glm::vec3 specular;
   float shininess;
   
};
#endif