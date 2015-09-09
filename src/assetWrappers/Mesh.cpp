#include "Mesh.h"
Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<GLuint> indices,
            std::vector<std::shared_ptr<Texture2D>> textures):
   vertices(vertices),
   indices(indices),
   textures(textures)
   {
      setupMesh();
   }

void Mesh::setupMesh()
{
   vBuffer.setData(vertices);
   ebo.setData(indices);
   //Layout numbers chosen from Layouts in shader, should provide a better
   //way to do this later...

   vao.addAttribute(0,vBuffer,sizeof(Vertex));
   vao.addAttribute(1,vBuffer,sizeof(Vertex),offsetof(Vertex, normal));
   vao.addAttribute(2, vBuffer,sizeof(Vertex),offsetof(Vertex,texCoords),2);
   vao.addElementArray(ebo);

}

void Mesh::render(Program & program)
{

   vao.bind();
   int numDiffuseTextures = 0;
   int numSpecularTextures = 0;

   Program::UniformArrayInfo diffuseTextures = program.getArray("diffuseTextures");
   Program::UniformArrayInfo specularTextures = program.getArray("specularTextures");

   for (std::vector<std::shared_ptr<Texture2D>>::iterator i = textures.begin(); i != textures.end(); ++i)
   {
      if((*i)->textureType() == TextureType::DIFFUSE)
      {
         if(diffuseTextures.size() < numDiffuseTextures)
         {
            (*i)->enable(diffuseTextures[numDiffuseTextures++]);
         }
      }
      else if((*i)->textureType() == TextureType::SPECULAR)
      {
         if(specularTextures.size() < numSpecularTextures)
         {
            (*i)->enable(specularTextures[numSpecularTextures++]);
         }
      }
   }
   glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);

   vao.unbind();

   for (std::vector<std::shared_ptr<Texture2D>>::iterator i = textures.begin(); i != textures.end(); ++i)
   {
      (*i)->disable();
   }
}