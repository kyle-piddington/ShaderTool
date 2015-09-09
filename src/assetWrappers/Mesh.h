#ifndef __MESH_H__
#define __MESH_H__
#include <vector>
#include "Texture2D.h"
#include "Program.h"
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"
struct Vertex
{
   glm::vec3 position;
   glm::vec3 normal;
   glm::vec2 texCoords;
};

/**
 * Assimp mesh container
 * A few assumptions are made about the programs here.
 */
class Mesh{
public:
   std::vector<Vertex> vertices;
   std::vector<GLuint> indices;
   std::vector<std::shared_ptr<Texture2D>> textures;

   Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<std::shared_ptr<Texture2D>> textures);
   void render(Program & prog);


private:
   VertexBuffer vBuffer;
   ElementBufferObject ebo;
   VertexArrayObject vao;

   void setupMesh();
   


};
#endif