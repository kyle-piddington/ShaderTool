#ifndef __LIGHT_H__
#define __LIGHT_H__
#include <glm/glm.hpp>
#include "../util/Transform.h"
#include <glfw/glfw3.h>
#include <vector>



struct Light
{
   Light(glm::vec3 amb, glm::vec3 diff, glm::vec3 specular, float dist);
   void bind(GLint posLoc, GLint ambLoc, GLint diffLoc, GLint specLoc, GLint constAttenLoc = -1, GLint linAttenLoc = -1, GLint quadAttenLoc = -1);
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