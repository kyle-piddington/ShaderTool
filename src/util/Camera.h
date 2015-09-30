#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Transform.h"
#include <glm/glm.hpp>
class Camera
{
public:
   Camera(float width, float height);
   void setPosition(glm::vec3 position);
   void translate(glm::vec3 translation, Space::spaceType type = Space::WORLD);
   void setRotation(glm::vec3 rotation);
   void rotate(glm::vec3 rotation);
   void lookAt(glm::vec3 position);
   void setFOV(float fov);
   void setAspectRatio(float aspectRatio);
   glm::mat4 getPerspectiveMatrix();
   glm::mat4 getOrthographicMatrix();
   glm::mat4 getViewMatrix();
   glm::vec3 getPosition();
   
   Transform transform;

private:
   float fov;
   float aspectRatio;
   float width;
   float height;
   bool dirty;

   glm::mat4 currentPerspectiveMtx;
   glm::mat4 currentViewMatrix;
   glm::mat4 currentOrthographicsMtx;


};
#endif