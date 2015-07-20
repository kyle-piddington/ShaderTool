#include "Camera.h"
#include "World.h"
Camera::Camera(float width, float height):
   fov(45.0),
   aspectRatio(width/height),
   width(width),
   height(height),
   position(glm::vec3(0.0)),
   transform(glm::mat4(1.0)),
   currentViewMatrix(glm::mat4(1.0)),
   currentPerspectiveMtx(glm::perspective(fov,aspectRatio,0.1f,100.0f)),
   currentOrthographicsMtx(glm::ortho(0.f,width,0.f,height,0.1f,100.f))
{

}
void Camera::setPosition(glm::vec3  position)
{
   transform =    glm::mat4(1,0,0,position.x,
                                     0,1,0,position.y,
                                     0,0,1,position.z,
                                     0,0,0,1) * glm::perspective(fov,aspectRatio,0.1f,100.0f);
   this->position = position;
   currentViewMatrix = glm::inverse(transform);
}
void Camera::lookAt(glm::vec3 target)
{
   currentViewMatrix = glm::lookAt(position, target, World::Up);
}
glm::mat4 Camera::getViewMatrix()
{
   return currentViewMatrix;
}
glm::mat4 Camera::getPerspectiveMatrix()
{
   return currentPerspectiveMtx;
}

