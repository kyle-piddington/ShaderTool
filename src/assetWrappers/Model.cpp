#include "Model.h"
#include "easyLogging++.h"
#include "TextureManager.h"
#include <glm/gtc/type_ptr.hpp>


Model::Model(std::string path)
{
   loadModel(path);
}

void Model::render(Program & prog)
{
   for (std::vector<std::shared_ptr<Mesh> >::iterator mesh = meshes.begin(); mesh != meshes.end(); ++mesh)
   {
      (*mesh)->render(prog);
   }
}

void Model::loadModel(std::string path)
{
   std::vector<tinyobj::shape_t> shapes;
   std::vector<tinyobj::material_t> materials;

   std::string err;
   LoadObj(shapes,materials, err, path.c_str());

   if(!err.empty())
   {
      LOG(ERROR) << "Could not load model: " + err;
   }
   /**
    * Process all the meshes
    */
   
   {
      for (std::vector<tinyobj::shape_t>::iterator i = shapes.begin(); i != shapes.end(); ++i)
      {

         meshes.push_back(processMesh(i->mesh));
      }
   }

}

std::shared_ptr<Mesh> Model::processMesh(tinyobj::mesh_t & mesh)
{
   std::vector<Vertex> vertices;
   std::vector<GLuint> indices;
   bool meshHasNorms = mesh.normals.size() == mesh.positions.size();
   bool meshHasTexCoords = mesh.texcoords.size()/2 == mesh.positions.size()/3;
   for(GLuint i = 0; i < mesh.positions.size()/3; i++)
   {
      int vertIdx = 3*i;
      int texIdx =  2*i;
      Vertex vertex;
      glm::vec3 vector;
      vector.x = mesh.positions[vertIdx + 0];
      vector.y = mesh.positions[vertIdx + 1];
      vector.z = mesh.positions[vertIdx + 2];
      vertex.position = vector;

      glm::vec3 normal;
      if(meshHasNorms)
      {
         normal.x = mesh.normals[vertIdx + 0];
         normal.y = mesh.normals[vertIdx + 1];
         normal.z = mesh.normals[vertIdx + 2];
         vertex.normal = normal;
      }
      else
      {
         vertex.normal = glm::vec3(0.0);
      }

      if(meshHasTexCoords) // Does the mesh contain texture coordinates?
      {
         glm::vec2 texCoord;
         texCoord.x = mesh.texcoords[texIdx + 0];
         texCoord.y = mesh.texcoords[texIdx + 1];
         vertex.texCoords = texCoord;
      }
      else
      {
         vertex.texCoords = glm::vec2(0.0);
      }
      vertices.push_back(vertex);
   }
   /* Copy the idx array*/
   indices = std::vector<unsigned int>(mesh.indices);
   std::cout << "Loading with " << vertices.size() << " Verts " << std::endl;
   return std::shared_ptr<Mesh>(new Mesh(vertices, indices));
}

