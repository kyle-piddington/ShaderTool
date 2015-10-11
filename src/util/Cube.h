#ifndef __CUBE_H__
#define __CUBE_H__
#include "Transform.h"
#include "VertexArrayObject.h"
#include "Program.h"
/**
 * Create a 1x1x1 cube centered at the origin
 */
class Cube
{
public:
   Cube();
   ~Cube();
   void render();
   Transform transform;
private:
   std::shared_ptr<VertexArrayObject>  getVAO();
   static std::shared_ptr<VertexArrayObject> cubeVao;
   static bool initted;
   static void initVAO();
   static int numInds;

};
#endif