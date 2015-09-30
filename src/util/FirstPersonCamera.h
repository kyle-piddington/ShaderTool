#ifndef __FirstPerson_CAM_H__
#define __FirstPerson_CAM_H__
#include "Camera.h"
#include "Context.h"
#include "Transform.h"
class FirstPersonCamera : public Camera
{
public:
   float Cam_Rot_Speed;
   float Cam_Move_Speed;
   FirstPersonCamera(float width, float height);
   void update(const Context * ctx);

private:
   float phi;
   float theta;
   glm::vec3 xyz;
};
#endif