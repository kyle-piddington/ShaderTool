#ifndef __HDR_SCENE_H__
#define __HDR_SCENE_H__
#include "Cube.h"
#include "Plane.h"
#include "EmptyScene.h"

#include "TexturedMaterial.h"
#include "Light.h"
#include "FirstPersonCamera.h"
#include "Framebuffer.h"
class HDRScene : public EmptyScene
{
   public:
      HDRScene(Context * ctx);
      void initPrograms();
      void initialBind();
      void render();
      void update();
      void cleanup();
   private:
      Program * hdrExposureProg;
      Program * hdrPostProcessProg;
      Light lights[4];
      Plane postprocessQuad;
      Cube tunnel;
      FirstPersonCamera camera;
      Framebuffer framebuffer;
      TexturedMaterial woodTex;



};
#endif