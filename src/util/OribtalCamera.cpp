#include "OrbitalCamera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <glm/gtx/rotate_vector.hpp>//GLM_GTX_rotate_vector
OrbitalCamera::OrbitalCamera(float w, float h):
   Camera(w,h),
   phi(0),
   theta(0),
   radius(3),
   Cam_Rot_Speed(2*M_PI),
   Cam_Zoom_Speed(3.0)
   {

   }
void OrbitalCamera::update(const Context * ctx)
{
   glm::vec3 rotate(0.0);
   if(Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT))
   {
      if(Keyboard::isKeyDown(GLFW_KEY_LEFT_SHIFT))
      {
         radius += (Mouse::getLastY() - Mouse::getY())/(float)(ctx->getWindowHeight())/2.0 * Cam_Zoom_Speed;
      }

      else
      {

         rotate.y = (Mouse::getLastY() - Mouse::getY())/(float)(ctx->getWindowHeight())/2.0 * Cam_Rot_Speed;
         rotate.x = (Mouse::getLastX() - Mouse::getX())/(float)(ctx->getWindowWidth())/2.0 * Cam_Rot_Speed;
         phi += rotate.y;
         theta += rotate.x;
         rotate.z = 0;
      }

   }
   glm::vec3 position(0,0,radius);
   position = glm::rotateX(position,phi);
   position = glm::rotateY(position,theta);

   setPosition(position);
   lookAt(glm::vec3(0,0,0));
}

