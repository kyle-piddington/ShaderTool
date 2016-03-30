#ifndef __RenderInfoController_H__
#define __RenderInfoController_H__
#include <glm/glm.hpp>
/**
 * Small controller for storing and loading
 * texture coordinate information.
 */
struct RenderInfoController
{
   RenderInfoController();
   glm::vec3 getPosition();
   void setPosition(glm::vec3 pos);
   glm::vec3 getNormal();
   void setNormal(glm::vec3 normal);
   glm::vec3 getTexCoord();
   void setTexCoord(glm::vec3 coord);


private:
   glm::vec3 pos;
   glm::vec3 nor;
   glm::vec3 texCoord;
};
#endif