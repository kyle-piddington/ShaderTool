#include "DirectionalLight.h"
#include <glm/gtc/type_ptr.hpp>
DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 amb, glm::vec3 diffuse, glm::vec3 specular):
direction(direction),
ambient(amb),
diffuse(diffuse),
specular(specular)
{

}


void DirectionalLight::bind(GLint dirLoc, GLint ambLoc, GLint diffLoc, GLint specLoc)
{
   glUniform3fv(dirLoc,1,glm::value_ptr(direction));
   glUniform3fv(ambLoc,1,glm::value_ptr(ambient));
   glUniform3fv(diffLoc,1,glm::value_ptr(diffuse));
   glUniform3fv(specLoc,1,glm::value_ptr(specular));
}

void DirectionalLight::bind(const GL_Structure & dirStruct)
{
   bind(dirStruct["direction"],
        dirStruct["ambient"],
        dirStruct["diffuse"],
        dirStruct["specular"]);
}

//Constants named in phong_frag_textured.fs
GL_Structure DirectionalLight::getStruct()
{
   GL_Structure glStruct;
   glStruct.addAttribute("direction");
   glStruct.addAttribute("ambient");
   glStruct.addAttribute("diffuse");
   glStruct.addAttribute("specular");
   return glStruct;
}
