#include "TabletopCamera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <glm/gtx/rotate_vector.hpp>//GLM_GTX_rotate_vector
TabletopCamera::TabletopCamera(float w, float h):
   Camera(w,h),
   phi(0),
   theta(0),
   radius(3),
   Cam_Rot_Speed(2*M_PI),
   Cam_Zoom_Speed(3.0)
   {
      transform.setParent(&centerPoint);
   }
void TabletopCamera::update(const Context * ctx)
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
   centerPoint.setRotation(glm::vec3(phi,theta,0.0));
   setPosition(glm::vec3(0,0,radius));
}

void TabletopCamera::rotate(float dPhi, float dTheta)
{
   phi += dPhi;
   theta += dTheta;
   centerPoint.setRotation(glm::vec3(phi,theta,0.0));

}




