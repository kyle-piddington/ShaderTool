#ifndef __SSAO_RENDERER_H__
#define __SSAO_RENDERER_H__
#include "CameraScene.h"
#include "Model.h"
#include "Plane.h"
#include "Framebuffer.h"
#include "Cube.h"
class SSAOScene : public CameraScene
{
public:
   SSAOScene(Context * ctx);

   void initPrograms();
   void initialBind();
   void render();
   void update();
   void cleanup();
private:

   void renderGeomoetry();
   void renderSSAO();
   void renderSSAOMap();
   void blurSSAO();
   void renderDeferred();
   std::vector<glm::vec3> generateSampleKernal(int numSamples);
   Framebuffer gBuffer, ssaoBuffer, ssaoBlurBuffer;
   Program * deferredGBufferProg;
   Program * ssaoProgram;
   Program * postProcessProg;
   Program * ssaoBlurProgram;
   Program * finalPassProgram;
   Plane renderPlane;
   Plane geomPlane;
   Model cryModel;
   Plane plane;
   Cube cube;

   Texture2D ssaoNoise;


};
#endif