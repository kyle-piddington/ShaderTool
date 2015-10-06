#ifndef __DEFERRED_RENDERER_H__
#define __DEFERRED_RENDERER_H__
#include "CameraScene.h"
#include "Model.h"
#include "Plane.h"
#include "Framebuffer.h"
#include "Cube.h"
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
   Program * debugProg;
   Plane renderPlane;
   Model cryModel;
   Cube cube;
   std::vector<glm::vec3> lightPositions;
   std::vector<glm::vec3> lightColors;

};
#endif