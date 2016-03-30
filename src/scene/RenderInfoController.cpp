#include "RenderInfoController.h"

RenderInfoController::RenderInfoController():
   pos(0.0),
   nor(0.0),
   texCoord(0.0)
   {

   }
void RenderInfoController::setPosition( glm::vec3 pos)
{
   this->pos = pos;
}
glm::vec3 RenderInfoController::getPosition()
{
   return pos;
}
void RenderInfoController::setNormal(glm::vec3 normal)
{
   this->nor = normal;
}
glm::vec3 RenderInfoController::getNormal()
{
   return this->nor;
}
void RenderInfoController::setTexCoord(glm::vec3 coord)
{
   this->texCoord = coord;
}
glm::vec3 RenderInfoController::getTexCoord()
{
   return this->texCoord;
}
