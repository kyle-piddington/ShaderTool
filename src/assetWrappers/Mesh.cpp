#include "Mesh.h"
#include "GL_Logger.h"
Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<GLuint> indices,
           std::vector<std::shared_ptr<Texture2D>> textures,
           std::vector<int> boneInds,
           std::vector<float>boneWeights):
   vertices(vertices),
   indices(indices),
   textures(textures),
   processBones(false)
   {
      if(boneInds.size() > 0 && boneWeights.size())
      {
         if(boneInds.size() == boneWeights.size())
         {

            processBones = true;
            boneIndBuffer = std::unique_ptr<VertexBuffer>(new VertexBuffer());
            boneWeightBuffer = std::unique_ptr<VertexBuffer>(new VertexBuffer());
              
         }
         else
         {
            LOG(WARNING) << "Bone inds and bone weights do not match!";
         }
      }
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
      if((*i)->textureType() == TextureType::DIFFUSE && diffuseTextures.isValid)
      {
         if(numDiffuseTextures < diffuseTextures.size())
         {
            (*i)->enable(diffuseTextures[numDiffuseTextures++]);
         }
      }
      else if((*i)->textureType() == TextureType::SPECULAR)
      {
         if(numSpecularTextures  < specularTextures.size() &&  specularTextures.isValid)
         {
            (*i)->enable(specularTextures[numSpecularTextures++]);
         }
      }
   }

   //Set uniforms for number of textures
   if(program.hasAddedUniform("numDiffuseTextures"))
   {
      program.getUniform("numDiffuseTextures").bind(numDiffuseTextures);
   }
   if(program.hasAddedUniform("numSpecularTextures"))
   {
      program.getUniform("numSpecularTextures").bind(numSpecularTextures);
   }

   glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
   vao.unbind();

   for (std::vector<std::shared_ptr<Texture2D>>::iterator i = textures.begin(); i != textures.end(); ++i)
   {
      (*i)->disable();
   }
}