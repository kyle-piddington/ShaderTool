#include "Spotlight.h"
#include <glm/gtc/type_ptr.hpp>

Spotlight::Spotlight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float cutOff, float outerCutOff, float range):
light(amb,diff,spec,range),
cutOff(cutOff),
outerCutOff(outerCutOff)
{

}
void Spotlight::bind(GLint posLoc, GLint dirLoc, GLint ambLoc, GLint diffLoc, GLint specLoc, GLint cutOffLoc, GLint outerCutOffLoc, GLint constAttenLoc, GLint linAttenLoc, GLint quadAttenLoc)
{
   light.bind(posLoc,ambLoc,diffLoc,specLoc,constAttenLoc,linAttenLoc,quadAttenLoc);
   glm::vec3 dir = light.transform.forward();
   glUniform3fv(dirLoc,1,glm::value_ptr(dir));
   glUniform1f(cutOffLoc,cutOff);
   glUniform1f(outerCutOffLoc,outerCutOff);
};
void Spotlight::setRange(float range)
{
   light.setRange(range);
}

Transform & Spotlight::transform()
{
   return light.transform;
}

GL_Structure Spotlight::getStruct()
{
   GL_Structure template_spotlight = Light::getStruct();
   template_spotlight.addAttribute("direction");
   template_spotlight.addAttribute("cutOff");
   template_spotlight.addAttribute("outerCutOff");
   return template_spotlight;
}