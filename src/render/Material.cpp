#include "Material.h"
#include <glm/gtc/type_ptr.hpp>


Material::Material(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shininess):
ambient(amb),
diffuse(diff),
specular(spec),
shininess(shininess)
{

}

void Material::bind(GLint ambLoc, GLint diffLoc, GLint specLoc, GLint shininessLoc)
{
   glUniform3fv(ambLoc,1,glm::value_ptr(ambient));
   glUniform3fv(diffLoc,1,glm::value_ptr(diffuse));
   glUniform3fv(specLoc,1,glm::value_ptr(specular));
   glUniform1f(shininessLoc,shininess);
}

GL_Structure Material::getStruct()
{
   GL_Structure template_material;
   template_material.addAttribute("diffuse");
   template_material.addAttribute("specular");
   template_material.addAttribute("emission");
   template_material.addAttribute("shininess");
   return template_material;
}