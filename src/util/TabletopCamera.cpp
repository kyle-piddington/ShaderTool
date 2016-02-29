#include "TabletopCamera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <glm/gtx/rotate_vector.hpp>//GLM_GTX_rotate_vector
#include <iostream>

TabletopCamera::TabletopCamera(float w, float h):
   Camera(w,h),
   phi(0),
   theta(0),
   radius(3),
   Cam_Rot_Speed(2*M_PI),
   Cam_Zoom_Speed(0.25)
   {
      transform.setParent(&centerPoint);
   }
void TabletopCamera::update(const Context * ctx)
{
   glm::vec3 rotate(0.0);
   if(Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT))
   {
  
      if(Keyboard::isKeyDown(GLFW_KEY_SPACE))
      {
         if(!isTranslating)
         {
            transLockPoint = centerPoint.getPosition();
            transMouseLockPoint = glm::vec2(Mouse::getX(), Mouse::getY());
            isTranslating = true;
         }
         glm::vec2 moveDelt = transMouseLockPoint - glm::vec2(Mouse::getX(), Mouse::getY());
         moveDelt /= glm::vec2(ctx->getWindowWidth(),ctx->getWindowHeight());
         moveDelt *= radius;
         centerPoint.setPosition(transLockPoint + this->transform.right(Space::WORLD) * moveDelt.x -this->transform.up(Space::WORLD) * moveDelt.y );
      }
      else
      {
         isTranslating = false;
         rotate.y = (Mouse::getLastY() - Mouse::getY())/(float)(ctx->getWindowHeight())/2.0 * Cam_Rot_Speed;
         rotate.x = (Mouse::getLastX() - Mouse::getX())/(float)(ctx->getWindowWidth())/2.0 * Cam_Rot_Speed;
         phi += rotate.y;
         theta += rotate.x;
         rotate.z = 0;
      }


   }
   else
   {
      isTranslating = false;
   }
   radius += Mouse::getScrollYDelta() * Cam_Zoom_Speed;
   centerPoint.setRotation(glm::vec3(phi,theta,0.0));
   setPosition(glm::vec3(0,0,radius));
}

void TabletopCamera::rotate(float dPhi, float dTheta)
{
   phi += dPhi;
   theta += dTheta;
   centerPoint.setRotation(glm::vec3(phi,theta,0.0));
}




