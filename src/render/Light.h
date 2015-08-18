#ifndef __LIGHT_H__
#define __LIGHT_H__
#include <glm/glm.hpp>
#include "../util/Transform.h"
#include <glfw/glfw3.h>
struct Light
{
   Light(glm::vec3 amb, glm::vec3 diff, glm::vec3 specular);
   void bind(GLint posLoc, GLint ambLoc, GLint diffLoc, GLint specLoc);
   glm::vec3 ambient;
   glm::vec3 diffuse;
   glm::vec3 specular;
   Transform transform;
private:
   glm::vec3 position;


};
#endif