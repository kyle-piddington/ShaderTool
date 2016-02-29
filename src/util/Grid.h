#ifndef __GRID_H_
#define __GRID_H_
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "Program.h"
class Grid
{
public:
   Grid(float w, float h, int xRes, int yRes);
   void render(Program & prog);

private:
   VertexArrayObject gridVAO;
   VertexBuffer bfr;


};
#endif