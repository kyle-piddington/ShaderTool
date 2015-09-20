#ifndef __SHADOW_SCENE_H__
#define __SHADOW_SCENE_H__
#include "CameraScene.h"
class ShadowScene : public CameraScene
{
public:
   ShadowScene(Context * ctx);
   virtual void initPrograms();
   virtual void initialBind();
   virtual void render();
   void cleanup();
private:
   Framebuffer depthBuffer;
   Light pointLight;
};
#endif