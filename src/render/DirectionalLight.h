#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__ 
#include "UniformObject.h"
#include <glm/glm.hpp>
#include <glfw/glfw3.h>

struct DirectionalLight
{
   DirectionalLight(glm::vec3 direction, glm::vec3 amb, glm::vec3 spec, glm::vec3 specular);
   void bind(const UniformObject & dirLoc, const UniformObject & ambLoc, const UniformObject & diffLoc, const UniformObject & specLoc);
   void bind(const UniformObject & dirStruct);

   glm::vec3 direction;
   glm::vec3 ambient;
   glm::vec3 diffuse;
   glm::vec3 specular;
};
#endif