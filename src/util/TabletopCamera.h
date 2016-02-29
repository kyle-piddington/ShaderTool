#ifndef __TABLETOP_CAM_H__
#define __TABLETOP_CAM_H__
#include "Camera.h"
#include "Context.h"
#include "Transform.h"
class TabletopCamera : public Camera
{
public:
   float Cam_Rot_Speed;
   float Cam_Zoom_Speed;
   TabletopCamera(float width, float height);
   void update(const Context * ctx);
   void rotate(float dPhi, float dTheta);
private:
   float phi;
   float theta;
   float radius;
   Transform centerPoint;
   glm::vec3 mouseDownPt;
   glm::vec2 transMouseLockPoint;
   glm::vec3 transLockPoint;
   bool isTranslating;

};
#endif