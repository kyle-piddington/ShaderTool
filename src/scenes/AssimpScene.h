#ifndef __ASSIMP_SCENE__
#define __ASSIMP_SCENE__
#include "Model.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"
#include "EmptyScene.h"
#include "Light.h"
class AssimpScene : public EmptyScene
{
public:
   AssimpScene(Context * ctx);

   virtual void initPrograms();
   
   virtual void initialBind();

   virtual void render();

   virtual void update();

private:
   Light light1, light2;
   Camera * camera;
   Model * model;
   Program * assimpProg;
   void handleCameraInput();
   glm::mat3 createNormalMatrix(const glm::mat4 & view, const glm::mat4 & model);
   float pitch;
   float yaw;


};
#endif