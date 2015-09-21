#ifndef __POSTPROCESS_SCENE_H__
#define __POSTPROCESS_SCENE_H__
#include "CameraScene.h"
#include "Cube.h"
#include "Texture2D.h"
#include "Plane.h"
#include "Framebuffer.h"
class PostProcessScene :public CameraScene
{
public:
   PostProcessScene(Context * ctx);
   virtual ~PostProcessScene();
   virtual void initPrograms();

   virtual void initialBind();

   virtual void render();

   virtual void update();

   virtual void cleanup();
private:

   void renderGeometry();
   void renderFrameBuffer();

   Program * texProg;
   Program * postprocessProg;
   Texture2D metal, marble;
   Plane plane, renderPlane;
   Cube cube1, cube2;

   Framebuffer fbo;

};
#endif