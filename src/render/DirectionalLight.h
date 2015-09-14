#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__ 
#include "GL_Structure.h"
#include <glm/glm.hpp>
#include <glfw/glfw3.h>

struct DirectionalLight
{
   DirectionalLight(glm::vec3 direction, glm::vec3 amb, glm::vec3 spec, glm::vec3 specular);
   void bind(GLint dirLoc, GLint ambLoc, GLint diffLoc, GLint specLoc);
   void bind(const GL_Structure & dirStruct);
   
   static GL_Structure getStruct();

   glm::vec3 direction;
   glm::vec3 ambient;
   glm::vec3 diffuse;
   glm::vec3 specular;
};
#endif