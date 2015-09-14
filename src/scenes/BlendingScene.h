#ifndef __BLENDING_SCENE_H__
#define __BLENDING_SCENE_H__
#include "CameraScene.h"
#include "Cube.h"
#include "Texture2D.h"
#include "Plane.h"
class BlendingScene :public CameraScene
{
public:
   BlendingScene(Context * ctx);
   virtual ~BlendingScene();
   virtual void initPrograms();

   virtual void initialBind();

   virtual void render();

   virtual void update();
private:

   Program * alphaTexProg;
   Texture2D metal, marble, window;
   Plane plane, windowQuad;
   Cube cube1, cube2;
   std::vector<glm::vec3> sortedTransparentObjects;
    
};
#endif