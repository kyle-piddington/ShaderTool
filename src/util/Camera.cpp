#include "Camera.h"
#include "World.h"
Camera::Camera(float width, float height):
   fov(45.0),
   aspectRatio(width/height),
   width(width),
   height(height),
   currentViewMatrix(glm::mat4(1.0)),
   currentPerspectiveMtx(glm::perspective(fov,aspectRatio,0.1f,100.0f)),
   currentOrthographicsMtx(glm::ortho(0.f,width,0.f,height,0.1f,100.f))
{

}
void Camera::setPosition(glm::vec3  position)
{
   transform.setPosition(position);
   this->currentViewMatrix = glm::inverse(transform.getMatrix());
}
void Camera::lookAt(glm::vec3 target)
{
  transform.lookAt(target);
  this->currentViewMatrix = glm::inverse(transform.getMatrix());
}

glm::mat4 Camera::getViewMatrix()
{
   return currentViewMatrix;
}
glm::mat4 Camera::getPerspectiveMatrix()
{
   return currentPerspectiveMtx;
}

