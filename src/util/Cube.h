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
   int numInds;
   VertexArrayObject cubeVao;
   VertexBuffer bufferData;
};
#endif