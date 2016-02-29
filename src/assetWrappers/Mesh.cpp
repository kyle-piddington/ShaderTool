#include "Mesh.h"
#include "GL_Logger.h"
#include <glm/gtc/type_ptr.hpp>
Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<GLuint> indices):
   vertices(vertices),
   indices(indices)
   {
      
      setupMesh();
   }
Mesh::~Mesh()
{

}
void Mesh::setupMesh()
{
   vBuffer.setData(vertices);
   ebo.setData(indices);
   //Layout numbers chosen from Layouts in shader, should provide a better
   //way to do this later...

   vao.addAttribute(0,vBuffer,sizeof(Vertex));
   vao.addAttribute(1,vBuffer,sizeof(Vertex) ,offsetof(Vertex, normal));
   vao.addAttribute(2, vBuffer,sizeof(Vertex),offsetof(Vertex,texCoords),2);
   vao.addElementArray(ebo);

}

void Mesh::render(Program & program)
{

   vao.bind();
   glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
   vao.unbind();
  
}