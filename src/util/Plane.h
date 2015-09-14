#ifndef __PLANE_H__
#define __PLANE_H__
#include "Transform.h"
#include "Vertex.h"
#include "VertexArrayObject.h"
class Plane
{
public:
   Plane(int xRes = 0, int yRes = 0);
   void render();
   Transform transform;
private:
   VertexArrayObject planeVAO;
   int numIndicies;
};
#endif