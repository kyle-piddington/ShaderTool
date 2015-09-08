#include "Mesh.h"
Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<GLuint> indicies, 
            std::vector<Texture2D> textures):
   vertices(vertices),
   indicies(indicies),
   textures(textures)
   {
      setupMesh();
   }

void Mesh::setupMesh()
{
   vBuffer.setData(vertices);
   ebo.setData(indicies);
   //Layout numbers chosen from Layouts in shader, should provide a better
   //way to do this later...

   vao.addAttribute(0,vBuffer,sizeof(Vertex));
   vao.addAttribute(1,vBuffer,sizeof(Vertex),offsetof(Vertex, normal));
   vao.addAttribute(2, vBuffer,sizeof(Vertex),offsetof(Vertex,texCoords),2);
   vao.addElementArray(ebo);
   
}

void Mesh::render(Program & prog)
{
   vao.enable();
   
}