#ifndef __MOTION_SCENE_H__
#define __MOTION_SCENE_H__
#include "CameraScene.h"
#include "Cube.h"
#include "Texture2D.h"
#include "Plane.h"
#include "Framebuffer.h"
class MotionBlurScene :public CameraScene
{
public:
   MotionBlurScene(Context * ctx);
   virtual ~MotionBlurScene();
   virtual void initPrograms();

   virtual void initialBind();

   virtual void render();

   virtual void update();

   virtual void cleanup();
private:

   void renderGeometry();
   void renderFrameBuffer();

   Program * postProcessProg;
   Program * texProg;
   Plane plane, renderPlane;
   Cube cube1, cube2;
   Texture2D metal, marble;
   Framebuffer fbo;
   glm::mat4 g_ViewProjectionInverseMatrix;
   glm::mat4 g_PreviousViewProjectionMatrix;
    
};
#endif