#include "Grid.h"

Grid::Grid(float w, float h, int xRes, int yRes)
{
   //X lines
   std::vector<float> verts;
   verts.reserve(xRes * 3 + yRes * 3);
   for(int u = 0; u <= xRes; u++)
   {
      float x_pos = -(w/2) +  w * (float)u/xRes;
      verts.push_back(x_pos);
      verts.push_back(0);
      verts.push_back(-h/2);
      verts.push_back(x_pos);
      verts.push_back(0);
      verts.push_back(h/2);
   }
   for(int v = 0; v <= yRes; v++)
   {
      float y_pos = -(h/2) +  h * (float)v/yRes;
      verts.push_back(-w/2);
      verts.push_back(0);
      verts.push_back(y_pos);
      verts.push_back(w/2);
      verts.push_back(0);
      verts.push_back(y_pos);
   }
   bfr.setData(verts);
   gridVAO.addAttribute(0,bfr);
}

void Grid::render(Program & prog)
{
   gridVAO.bind();
   glDrawArrays(GL_LINES, 0, bfr.getNumVerts() * 3);
   gridVAO.unbind();
}