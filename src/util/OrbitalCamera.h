#ifndef __ORBITAL_CAM_H__
#define __ORBITAL_CAM_H__
#include "Camera.h"
#include "Context.h"
class OrbitalCamera : public Camera
{
public:
   float Cam_Rot_Speed;
   float Cam_Zoom_Speed;
   OrbitalCamera(float width, float height);
   void update(const Context * ctx);
private:
   float phi;
   float theta;
   float radius;

};
#endif