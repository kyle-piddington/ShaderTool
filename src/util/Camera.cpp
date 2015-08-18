#include "Camera.h"
#include "World.h"
Camera::Camera(float width, float height):
   fov(45.0),
   aspectRatio(width/height),
   width(width),
   height(height),
   dirty(true),
   currentViewMatrix(glm::mat4(1.0)),
   currentPerspectiveMtx(glm::perspective(fov,aspectRatio,0.1f,100.0f)),
   currentOrthographicsMtx(glm::ortho(-2.f,2.0f,-2.f/aspectRatio,2.0f/aspectRatio,0.1f,100.f))
{

}
void Camera::setPosition(glm::vec3  position)
{
   transform.setPosition(position);
   dirty = true;
}

void Camera::translate(glm::vec3 translation)
{
  transform.translate(translation);
  dirty = true;
}
void Camera::setRotation(glm::vec3 rotation)
{
  transform.setRotation(rotation);
  dirty = true;
}
void Camera::rotate(glm::vec3 rotation)
{
  transform.rotate(rotation);
  dirty = true;
}
void Camera::lookAt(glm::vec3 target)
{
  transform.lookAt(target);
  dirty=true;
}

glm::vec3 Camera::getPosition()
{
  return transform.getPosition();
}

glm::mat4 Camera::getViewMatrix()
{
  if(dirty)
  {
    this->currentViewMatrix = glm::inverse(transform.getMatrix());
    dirty = false;
  }
    
   return currentViewMatrix;
}
glm::mat4 Camera::getPerspectiveMatrix()
{
   return currentPerspectiveMtx;
}
glm::mat4 Camera::getOrthographicMatrix()
{
  return currentOrthographicsMtx;
}

