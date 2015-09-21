#ifndef __SHADOW_SCENE_H__
#define __SHADOW_SCENE_H__
#include "CameraScene.h"
#include "Framebuffer.h"
#include "Cube.h"
#include "Plane.h"
#include "Light.h"
class ShadowScene : public CameraScene
{
public:
   ShadowScene(Context * ctx);
   virtual void initPrograms();
   virtual void initialBind();
   virtual void render();
   virtual void cleanup();
private:
   std::unique_ptr<Framebuffer> depthBuffer;
   Program * depthPassProg, *postprocessProg;
   Cube renderCube;
   Plane postprocessPlane;
   Light pointLight;
};
#endif