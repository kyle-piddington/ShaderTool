#ifndef __SPOTLIGHT_H__
#define __SPOTLIGHT_H__
#include "Light.h"
#include "GL_Structure.h"
class Spotlight
{
public:
   Spotlight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float cutoff, float outerCutoff, float range);
   void bind(GLint posLoc, GLint dirLoc, GLint ambLoc, GLint diffLoc, GLint specLoc, GLint cutOff, GLint outerCutoff, GLint constAttenLoc = -1, GLint linAttenLoc = -1, GLint quadAttenLoc = -1);
   void setRange(float range);
   Transform & transform();
   static GL_Structure getStruct();
   float cutOff;
   float outerCutOff;
private:
   Light light;
};
#endif