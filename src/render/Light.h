#ifndef __LIGHT_H__
#define __LIGHT_H__
#include "UniformObject.h"
#include <glm/glm.hpp>
#include "../util/Transform.h"
#include <glfw/glfw3.h>
#include <vector>



struct Light
{
   Light();
   Light(glm::vec3 amb, glm::vec3 diff, glm::vec3 specular, float dist);
   void bind(const UniformObject &  posLoc,
             const UniformObject &  ambLoc,
             const UniformObject &  diffLoc,
             const UniformObject &  specLoc,
             const UniformObject &  constAttenLoc = UniformObject::InvalidObject,
             const UniformObject &  linAttenLoc   = UniformObject::InvalidObject, 
             const UniformObject &  quadAttenLoc  = UniformObject::InvalidObject);
   
   void bind(const UniformObject & lightStruct);
   
   void setRange(float range);
   glm::vec3 ambient;
   glm::vec3 diffuse;
   glm::vec3 specular;
   
   Transform transform;

private:
   struct attenuationStruct
   {
         float range;
         double linear;
         double quadratic;
         attenuationStruct(float range, double linear, double quadratic):
         range(range),
         linear(linear),
         quadratic(quadratic){}

   };

   static std::vector<attenuationStruct> attenuationTable;
   static attenuationStruct getAttenuationForDist(float dist);
   static void initializeAttenuationTable();
   
   glm::vec3 position;
   attenuationStruct currentAttenuation;
   float constAtten;
   float linearAtten;
   float quadraticAtten;



};


#endif