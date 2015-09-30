#ifndef __HDR_SCENE_H__
#define __HDR_SCENE_H__
#include "Cube.h"
#include "Plane.h"
#include "EmptyScene.h"
#include "Texture2D.h"

#include "FirstPersonCamera.h"
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
      Program * hrdProg;
      Plane postprocessQuad;
      Cube tunnel;
      FirstPersonCamera camera;
      Texture2D woodTex;



};
#endif