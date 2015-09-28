#ifndef __VISUALIZENORMALSCENE_H__
#define __VISUALIZENORMALSCENE_H__
#include "AssimpScene.h"
#include "Model.h"
class VisualizeNormalScene : public CameraScene
{
public:
   VisualizeNormalScene(Context * ctx);
   virtual void initPrograms();
   virtual void initialBind();
   virtual void render();


private: 
   void renderGeometry(Program * prog);
   Program * visualizeNormalProgram, *drawModelProg;
   Model model;
};
#endif