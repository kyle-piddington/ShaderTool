#ifndef __SHADOW_SCENE_H__
#define __SHADOW_SCENE_H__
#include "CameraScene.h"
#include "Framebuffer.h"
#include "Cube.h"
#include "Plane.h"
#include "Light.h"
#include "Texture2D.h"
#include "Model.h"
class ShadowScene : public CameraScene
{
public:
   ShadowScene(Context * ctx);
   virtual void initPrograms();
   virtual void initialBind();
   virtual void render();
   virtual void cleanup();
   virtual void update();
private:
   void renderGeometry(Program & prog, GLint modelMtx, GLint normalMtx = -1, GLint texMtx = -1);
   void renderDepthPass();
   void renderDepthMap();
   void renderGeometryWithShadows();
   Framebuffer depthBuffer;
   Program * depthPassProg, *postprocessProg, * phongTexShadowProg;
   Model model;
   Cube renderCube[3]{Cube()};
   Plane postprocessPlane, geomPlane;
   Texture2D woodTexture;
   Light pointLight;
};
#endif