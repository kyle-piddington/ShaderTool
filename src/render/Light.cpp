#include "Light.h"
#include <glm/gtc/type_ptr.hpp>
std::vector<Light::attenuationStruct> Light::attenuationTable;
  

//Static setup of attenuationTable table. Values taken from http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation 
void Light::initializeAttenuationTable()
{
   Light::attenuationTable.push_back(attenuationStruct(7,0.7,1.8));
   Light::attenuationTable.push_back(attenuationStruct(13, 0.35, 0.44));
   Light::attenuationTable.push_back(attenuationStruct(20, 0.22, 0.20));
   Light::attenuationTable.push_back(attenuationStruct(32, 0.14, 0.07));
   Light::attenuationTable.push_back(attenuationStruct(50, 0.09, 0.032));
   Light::attenuationTable.push_back(attenuationStruct(65, 0.07, 0.017));
   Light::attenuationTable.push_back(attenuationStruct(100, 0.045, 0.0075));
   Light::attenuationTable.push_back(attenuationStruct(160, 0.027, 0.0028));
   Light::attenuationTable.push_back(attenuationStruct(200, 0.022, 0.0019));
   Light::attenuationTable.push_back(attenuationStruct(325, 0.014, 0.0007));
   Light::attenuationTable.push_back(attenuationStruct(600, 0.007, 0.0002));
   Light::attenuationTable.push_back(attenuationStruct(3250, 0.0014, 0.000007));
}

Light::attenuationStruct Light::getAttenuationForDist(float dist)
{
   //Initialization of attenuation table
   if(Light::attenuationTable.size() == 0)
   {
     Light::initializeAttenuationTable();
   }
   if(dist < attenuationTable.begin()->range)
   {
      return *attenuationTable.begin();
   }

   std::vector<attenuationStruct>::iterator i,last;
   last = Light::attenuationTable.begin();
   for (i = Light::attenuationTable.begin(); i != Light::attenuationTable.end(); ++i)
   {
      if(dist < i->range)
      {
         float interp = (dist-last->range)/(i->range-last->range);
         return attenuationStruct(dist,(1-interp)*last->linear + interp*i->linear,
                                       (1-interp)*last->quadratic + interp*i->quadratic);
      }
      last = i;
   }

   return *(Light::attenuationTable.end() -1);

}
Light::Light(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec,float range):
ambient(amb),
diffuse(diff),
specular(spec),
currentAttenuation(getAttenuationForDist(range))
{
}

void Light::setRange(float range)
{
   currentAttenuation = getAttenuationForDist(fmax(range,1.0));
}

/**
 * Get a GLStruct representing this light
 * names are degined in phong_frag
 */
GL_Structure Light::getStruct()
{
   GL_Structure template_light;
   template_light.addAttribute("position");
   template_light.addAttribute("ambient");
   template_light.addAttribute("diffuse");
   template_light.addAttribute("specular");
   template_light.addAttribute("constant");
   template_light.addAttribute("linear");
   template_light.addAttribute("quadratic");
   return template_light;
}
void Light::bind(GLint posLoc, GLint ambLoc, GLint diffLoc, GLint specLoc, GLint constAtten, GLint linearAtten, GLint quadAtten)
{
   position = transform.getPosition();
   glUniform3fv(posLoc,1,glm::value_ptr(position));
   glUniform3fv(ambLoc,1,glm::value_ptr(ambient));
   glUniform3fv(diffLoc,1,glm::value_ptr(diffuse));
   glUniform3fv(specLoc,1,glm::value_ptr(specular));

   if(constAtten > -1)
   {
      glUniform1f(constAtten,1.0);
   }
   if(linearAtten > -1)
   {
      glUniform1f(linearAtten,currentAttenuation.linear);
   }
   if(quadAtten > -1)
   {
     glUniform1f(quadAtten,currentAttenuation.quadratic);
   }
   
}
