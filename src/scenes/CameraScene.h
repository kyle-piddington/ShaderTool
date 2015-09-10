#ifndef __CAMERA_SCENE__
#define __CAMERA_SCENE__
#include "Camera.h"
#include "EmptyScene.h"
#include "Keyboard.h"
#include "Mouse.h"
class CameraScene:public EmptyScene
{
public:
   CameraScene(Context * ctx);
   virtual ~CameraScene();
   virtual void update();
   Camera camera;
   float Cam_Speed = 1.0/10.0;
   float Cam_Rot_Speed = M_PI;

private:
   void handleCameraInput();
   float pitch;
   float yaw;

};
#endif