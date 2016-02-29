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
   std::vector<GLuint> indices;

   Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
   ~Mesh();
   void render(Program & prog);


private:
   VertexBuffer vBuffer;
   ElementBufferObject ebo;
   VertexArrayObject vao;
   void setupMesh();

   


};
#endif