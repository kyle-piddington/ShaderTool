#ifndef __DEFERRED_RENDERER_H__
#define __DEFERRED_RENDERER_H__
#include "CameraScene.h"
#include "Model.h"
#include "Plane.h"
#include "Framebuffer.h"
class DeferredRenderScene : public CameraScene
{
public:
   DeferredRenderScene(Context * ctx);

   void initPrograms();
   void initialBind();
   void render();
   void update();
private:

   enum RenderType
   {
      RENDER_POSITION = 0,
      RENDER_NORMAL = 1,
      RENDER_COLOR = 2,
      RENDER_SPECULAR = 3
   };
   RenderType currentRenderType;
   Framebuffer gBuffer;
   Program * deferredGBufferProg;
   Program * postProcessProg;
   Plane renderPlane;
   Model cryModel;

};
#endif