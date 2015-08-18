#include "Light.h"
#include <glm/gtc/type_ptr.hpp>


Light::Light(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec):
ambient(amb),
diffuse(diff),
specular(spec)
{}
void Light::bind(GLint posLoc, GLint ambLoc, GLint diffLoc, GLint specLoc)
{
   position = transform.getPosition();
   glUniform3fv(posLoc,1,glm::value_ptr(position));

   glUniform3fv(ambLoc,1,glm::value_ptr(ambient));
   glUniform3fv(diffLoc,1,glm::value_ptr(diffuse));
   glUniform3fv(specLoc,1,glm::value_ptr(specular));
   
}
