#ifndef __INSTANCING_SCENE_H__
#define __INSTANCING_SCENE_H__
#include "VertexArrayObject.h"
#include "EmptyScene.h"

class InstancingScene : public EmptyScene
{

public:
   InstancingScene(Context * ctx);
   void initPrograms();
   void initialBind();
   void render();
   void update();
private:
   Program * instanceProgram;
   VertexArrayObject quadVAO;



};
#endif