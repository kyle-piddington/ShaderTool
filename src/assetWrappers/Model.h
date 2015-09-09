#ifndef __MODEL_H__
#define __MODEL_H__
#include <vector>
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
/**
 * An Assimp renderable model
 */
class Model
{
public:
   Model(std::string path);
   void render(Program & prog);
private:
   std::vector<Mesh> meshes;
   std::string directory;
   void loadModel(std::string path);
   void processNode(aiNode * node, const aiScene * scene);
   Mesh processMesh(aiMesh * mesh, const aiScene * scene);
   std::vector<Texture> loadTextureMaterials(
      aiMaterial * mat, aiTextureType type,
      std::string typeName);
   


};

#endif