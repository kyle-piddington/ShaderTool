#ifndef __MESH_H__
#define __MESH_H__
#include <vector>
#include "Texture2D.h"
#include "Program.h"
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"
#include "Vertex.h"
#include "VertexBoneData.h"
/**
 * Assimp mesh container
 * A few assumptions are made about the programs here.
 */
class Mesh{
public:
   std::vector<Vertex> vertices;
   std::vector<VertexBoneData> boneData;
   std::vector<GLuint> indices;
   std::vector<std::shared_ptr<Texture2D>> textures;

   Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<std::shared_ptr<Texture2D>> textures,
         std::vector<int> boneInds = std::vector<int>(), std::vector<float> boneWeights = std::vector<float>());
   
   ~Mesh();
   void render(Program & prog);


private:
   VertexBuffer vBuffer;
   std::unique_ptr<VertexBuffer>  boneIndBuffer;
   std::unique_ptr<VertexBuffer>  boneWeightBuffer;

   ElementBufferObject ebo;
   VertexArrayObject vao;

   bool processBones;
   void setupMesh();
   


};
#endif