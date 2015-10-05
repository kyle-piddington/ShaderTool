#ifndef __NORMAL_SCENE_H__
#define __NORMAL_SCENE_H__
#include "CameraScene.h"
class NormalMapScene : public CameraScene
{
public:
   NormalMapScene(Context * ctx);
   void initPrograms();
   void initialBind();
   void render();
   void cleanup();
private:
   Program * normalMapProg;
   Texture diffuseMap;
   Texture normalMap;
   VertexArrayObject planeVAO;
};
#endif