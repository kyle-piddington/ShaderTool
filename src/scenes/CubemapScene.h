#ifndef __CUBEMAP_SCENE_H__
#define __CUBEMAP_SCENE_H__
#include "CameraScene.h"
#include "CubeMap.h"
#include "Cube.h"
#include "Texture2D.h"

class CubemapScene : public CameraScene
{
public:
   CubemapScene(Context * ctx);
   virtual void initPrograms();
   virtual void initialBind();
   virtual void render();
private:
   Program * texProg;
   Program * skyboxProg;
   Cube cube, skyboxCube;
   Texture2D crate;
   CubeMap cubeMap;
};
#endif