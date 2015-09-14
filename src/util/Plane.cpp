#include "Plane.h"

std::vector<Vertex> generatePlaneVertices(int xres, int zres)
{
   std::vector<Vertex> vertices;
   for(int z = 0; z <= zres; z++)
   {
      for(int x = 0; x <= xres; x++)
      {
         Vertex v;
         v.position = glm::vec3((x-xres/2.0)/(xres/2.0),0,(z-zres/2.0)/(zres/2.0));
         v.normal = glm::vec3(0,1,0);
         v.texCoords = glm::vec2(x/(float)xres,1-z/(float)zres);
         vertices.push_back(v);
      }
   }
   return vertices;
}
std::vector<GLuint> generatePlaneIndicies(int xres, int zres)
{
   std::vector<GLuint> indicies;
   for(int z = 0; z < zres; z++)
   {
     
      for(int x = 0; x < xres; x++)
      {
         int ll = x + z*(xres + 1);
         int lr = x + z*(xres + 1) + 1;
         int ul = x + (z + 1) * (xres+1);
         int ur = x + (z + 1) * (xres+1) + 1;
         indicies.push_back(ll);
         indicies.push_back(lr);
         indicies.push_back(ul);
         indicies.push_back(lr);
         indicies.push_back(ur);
         indicies.push_back(ul);
      }
   }
   return indicies;

}
Plane::Plane(int xres, int zres)
{
   VertexBuffer vbo;
   ElementBufferObject ebo;
   std::vector<Vertex> verts = generatePlaneVertices(xres,zres);
   std::vector<GLuint> inds = generatePlaneIndicies(xres, zres);
   vbo.setData(verts);
   ebo.setData(inds);
   planeVAO.addAttribute(0,vbo,sizeof(Vertex));
   planeVAO.addAttribute(1,vbo,sizeof(Vertex),offsetof(Vertex, normal));
   planeVAO.addAttribute(2, vbo,sizeof(Vertex),offsetof(Vertex,texCoords),2);
   planeVAO.addElementArray(ebo);
   numIndicies = ebo.getNumIndicies();

}

void Plane::render()
{
   planeVAO.bind();
   glDrawElements(GL_TRIANGLES, numIndicies, GL_UNSIGNED_INT, 0);
   planeVAO.unbind();



}