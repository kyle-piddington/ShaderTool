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

Light::Light():
ambient(glm::vec3(0.1)),
diffuse(glm::vec3(0.6)),
specular(glm::vec3(0.8)),
currentAttenuation(getAttenuationForDist(50.0))
{
   
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

void Light::bind(const UniformObject &  posLoc,
                 const UniformObject &  ambLoc,
                 const UniformObject &  diffLoc,
                 const UniformObject &  specLoc,
                 const UniformObject &  constAtten,
                 const UniformObject &  linearAtten,
                 const UniformObject &  quadAtten)

{
   position = transform.getPosition();
   posLoc.bind(position);
   ambLoc.bind(ambient);
   diffLoc.bind(diffuse);
   specLoc.bind(specular);

   if(constAtten.isValid())
   {
      constAtten.bind(1.0);
   }
   if(linearAtten.isValid())
   {
      linearAtten.bind(currentAttenuation.linear);
   }
   if(quadAtten.isValid())
   {
      quadAtten.bind(currentAttenuation.quadratic);
   }

}

void Light::bind(const UniformObject & lightObj)
{
   lightObj["position"].bind(position);
   lightObj["ambient"].bind(ambient);
   lightObj["diffuse"].bind(diffuse);
   lightObj["specular"].bind(specular);
   
   if(lightObj["constant"].isValid())
   {
      lightObj["constant"].bind(1.0);
   }
   if(lightObj["linear"].isValid())
   {
      lightObj["linear"].bind(currentAttenuation.linear);
   }
   if(lightObj["quadratic"].isValid())
   {
      lightObj["quadratic"].bind(currentAttenuation.quadratic);
   }
}
