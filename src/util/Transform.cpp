#include "Transform.h"
#include "World.h"
#include <iostream>
#include <easylogging++.h>
#include <glm/gtx/orthonormalize.hpp>
#define GLM_FORCE_RADIANS

Transform::Transform():
   position(glm::vec3(0)),
   rotation(glm::vec3(0.0)),
   localUp(glm::vec4(World::Up,0.0)),
   localRight(glm::vec4(World::Right,0.0)),
   localForward(glm::vec4(World::Forward,0.0))
   {

   }
void Transform::setPosition(const glm::vec3 & position)
{
   this->position = position;
}

void Transform::setRotation(const glm::vec3 & eulerAngles)
{

   this->rotation = glm::normalize(glm::quat(glm::vec3(0.0)) * glm::quat(eulerAngles));
   updateFrame();
}
void Transform::setRotation(float angle, const glm::vec3 & axis)
{
   //Assert axis greater than zero
   if(axis.length() == 0)
   {
      LOG(ERROR) << "Zero length axis used in angle axis rotation";
      assert(false);
   }
   glm::normalize(axis);

   this->rotation = glm::angleAxis(angle,axis);

   //glm::normalize(this->rotation);
   updateFrame();
}

void Transform::translate(const glm::vec3 & pos)
{
   this->position += pos;

}

void Transform::rotate(const glm::vec3 eulerAngles)
{
   this->rotation = glm::normalize(this->rotation * glm::quat(eulerAngles));
   updateFrame();
}

void Transform::rotate(float angle, const glm::vec3 & axis)
{
   if(axis.length() == 0)
   {
      LOG(ERROR) << "Zero length axis used in angle axis rotation";
      assert(false);
   }
   glm::normalize(axis);
   glm::quat newQuat = glm::angleAxis(angle,axis);
   this->rotation = this->rotation * newQuat;
   updateFrame();
}

glm::vec3 Transform::getPosition() const
{
   return position;
}
glm::quat Transform::getRotation() const
{
   return rotation;
}
glm::mat4  Transform::getMatrix() const
{
   glm::mat4 t =    glm::mat4(1,0,0,0,
                              0,1,0,0,
                              0,0,1,0,
                              this->position.x,this->position.y,this->position.z,1);
   return  t * glm::mat4_cast(rotation);
}

void Transform::lookAt(glm::vec3 target)
{
   /*Vector forward = lookAt.Normalized();
   Vector right = Vector::Cross(up.Normalized(), forward);
   Vector up = Vector::Cross(forward, right);*/

   glm::vec3 forward = glm::normalize(target-position);
   glm::vec3 up = glm::orthonormalize(World::Up, forward); // Keeps up the same, make forward orthogonal to up
   glm::vec3 right = glm::normalize(glm::cross(forward, up));

   glm::mat4 rotMat;
   rotMat[0] = glm::vec4(right.x,right.y,right.z,0);
   rotMat[1] = glm::vec4(up.x, up.y, up.z, 0);
   rotMat[2] = glm::vec4(-forward.x, -forward.y, -forward.z, 0);
   rotMat[3] = glm::vec4(0,0,0,1);
   //Create a quaternion from the three vectors above.
   glm::quat ret = glm::quat_cast(rotMat);
  

   this->rotation = ret;
   updateFrame();
   //Also reorient the up axis
   

   //localForward = newForward;
   

}

glm::vec3 Transform::up() const
{
   return glm::vec3(localUp);
}

glm::vec3 Transform::right() const
{
   return glm::vec3(localRight);
}

glm::vec3 Transform::forward() const
{
   return glm::vec3(localForward);
}

void Transform::updateFrame()
{

   glm::vec4 wUp(World::Up,0.0);
   glm::vec4 wRt(World::Right,0.0);
   glm::vec4 wFw(World::Forward,0.0);
   glm::mat4 rotMtx = glm::mat4_cast(rotation);
   localRight = glm::normalize(rotMtx * wRt);
   localUp = glm::normalize(rotMtx * wUp);
   localForward = glm::normalize(rotMtx * wFw);


}
