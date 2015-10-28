#include "Mesh.h"
#include "GL_Logger.h"
#include <glm/gtc/type_ptr.hpp>
Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<GLuint> indices,
           std::vector<std::shared_ptr<Texture2D>> textures,
           std::vector<VertexBoneData> boneData,
           std::vector<glm::mat4> boneOffsets):
   vertices(vertices),
   indices(indices),
   textures(textures),
   boneOffsets(boneOffsets),
   processBones(false)
   {
      if(boneData.size() > 0 )
      {
         processBones = true;
         boneBuffer = std::unique_ptr<VertexBuffer>(new VertexBuffer());
         boneBuffer->setData(boneData);
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
   if(processBones)
   {
      
      vao.addAttribute(3,*boneBuffer,sizeof(VertexBoneData),offsetof(VertexBoneData,boneIds),4,GL_FALSE,GL_INT);
      vao.addAttribute(4,*boneBuffer,sizeof(VertexBoneData),offsetof(VertexBoneData,boneWeights),4);
   }
   vao.addElementArray(ebo);

}

void Mesh::render(Program & program)
{

   vao.bind();
   int numDiffuseTextures = 0;
   int numSpecularTextures = 0;
   
   Program::UniformArrayInfo diffuseTextures = program.getArray("diffuseTextures");
   Program::UniformArrayInfo specularTextures = program.getArray("specularTextures");
   Program::UniformArrayInfo boneOffsetUniforms = program.getArray("gBinds");

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
   for(int i = 0; i < boneOffsets.size(); i++)
   {
      glUniformMatrix4fv(boneOffsetUniforms[i],1,GL_FALSE,glm::value_ptr(boneOffsets[i]));
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