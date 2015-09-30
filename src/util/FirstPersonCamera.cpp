#include "FirstPersonCamera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <glm/gtx/rotate_vector.hpp>//GLM_GTX_rotate_vector
FirstPersonCamera::FirstPersonCamera(float w, float h):
   Camera(w,h),
   phi(0),
   theta(0),
   Cam_Rot_Speed(2*M_PI),
   Cam_Move_Speed(0.1)
   {
   }
void FirstPersonCamera::update(const Context * ctx)
{
   glm::vec3 rotate(0.0);
   if(Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT))
   {
         rotate.y = (Mouse::getLastY() - Mouse::getY())/(float)(ctx->getWindowHeight())/2.0 * Cam_Rot_Speed;
         rotate.x = (Mouse::getLastX() - Mouse::getX())/(float)(ctx->getWindowWidth())/2.0 * Cam_Rot_Speed;
         phi += rotate.y;
         theta += rotate.x;
         rotate.z = 0;
   }
   glm::vec2 translateVec;
   if(Keyboard::isKeyDown(GLFW_KEY_W))
   {
      translateVec.y += Cam_Move_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_S))
   {
      translateVec.y -= Cam_Move_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_A))
   {
      translateVec.x -= Cam_Move_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_D))
   {
      translateVec.x += Cam_Move_Speed;
   }



   setRotation(glm::vec3(phi,theta,0.0));
   translate(transform.forward() * translateVec.y + transform.right() * translateVec.x);
}





