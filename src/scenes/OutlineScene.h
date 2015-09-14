#ifndef __OUTLINE_SCENE_H__
#define __OUTLINE_SCENE_H__
#include "CameraScene.h"
#include "Cube.h"
#include "Texture2D.h"
#include "Plane.h"
class OutlineScene :public CameraScene
{
public:
   OutlineScene(Context * ctx);
   virtual ~OutlineScene();
   virtual void initPrograms();

   virtual void initialBind();

   virtual void render();

   virtual void update();
private:

   Program * texProg;
   Program * outlineTextureProgram;
   Texture2D metal, marble;
   Plane plane;
   Cube cube1, cube2;

};
#endif