#ifndef __Anim_SCENE__
#define __Anim_SCENE__
#include "Model.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"
#include "CameraScene.h"
#include "Light.h"
#include "Cube.h"
#include "Material.h"
#include "Plane.h"
class AnimScene : public CameraScene
{
public:
   AnimScene(Context * ctx);

   virtual ~AnimScene();
   virtual void initPrograms();
   
   virtual void initialBind();

   virtual void render();

   virtual void update();

private:
   Light light1, light2;
   Model * model;
   Program * animProg;
   Program * debugProg;
   Plane plane;
   Cube cube;
   glm::mat3 createNormalMatrix(const glm::mat4 & view, const glm::mat4 & model);
   Material mat;

};
#endif