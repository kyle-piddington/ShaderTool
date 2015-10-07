#ifndef __NORMAL_SCENE_H__
#define __NORMAL_SCENE_H__
#include "CameraScene.h"
#include "Texture2D.h"
#include "VertexArrayObject.h"
class NormalMapScene : public CameraScene
{
public:
   NormalMapScene(Context * ctx);
   void initPrograms();
   void initialBind();
   void render();
   void update();
   void cleanup();
private:

  
   struct Point{
      glm::vec3 position;
      glm::vec3 normal;
      glm::vec2 texCoords;
      glm::vec3 tangent;
   };

   glm::vec3 getTangent(Point & pa, Point & pb, Point & pc);
   Program * frameDisplayProg;
   Program * normalMapProg;
   Texture2D diffuseMap;
   Texture2D normalMap;
   VertexArrayObject planeVAO;
   Transform planeTransform;
};
#endif