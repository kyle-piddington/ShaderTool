#ifndef __PLANE_H__
#define __PLANE_H__
#include "Transform.h"
#include "Vertex.h"
#include "VertexArrayObject.h"
class Plane
{
public:
   Plane(int xRes = 1, int yRes = 1);
   void render();
   Transform transform;
private:
   VertexArrayObject planeVAO;
   int numIndicies;
};
#endif