#ifndef __Bloom_SCENE_H__
#define __Bloom_SCENE_H__
#include "Cube.h"
#include "Plane.h"
#include "EmptyScene.h"

#include "TexturedMaterial.h"
#include "Light.h"
#include "FirstPersonCamera.h"
#include "Framebuffer.h"
#include "PingPongFramebuffer.h"

class BloomScene : public EmptyScene
{
   public:
      BloomScene(Context * ctx);
      void initPrograms();
      void initialBind();
      void render();
      void update();
      void cleanup();
   private:
      Program * bloomRenderProg;
      Program * gaussBlurProg;

      Program * framebufferCombineProg;

      Light lights[4];
      Plane postprocessQuad;
      Cube tunnel;
      FirstPersonCamera camera;
      
      Framebuffer extractionBuffer;
      PingPongFramebuffer blurBuffer;

      TexturedMaterial woodTex;

      int numBlurs;

};
#endif