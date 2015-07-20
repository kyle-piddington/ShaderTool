#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
   Transform();
   void setPosition(const glm::vec3 pos);
   void setRotation(const glm::vec3 eulerAngles);
   glm::vec3 getPosition() const;
   glm::fquat getRotation() const;
   glm::mat4 getMatrix() const;
   void lookAt(glm::vec3 target);
   

private:
   glm::vec3 position;
   glm::fquat rotation;

};
#endif