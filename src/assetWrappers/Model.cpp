#include "Model.h"
#include "easyLogging++.h"
Model::Model(std::string path)
{
   loadModel(path);
}
void Model::render(Program & prog)
{
   for (std::vector<Mesh>::iterator i = meshes.begin(); i != meshes.end(); ++i)
   {
      mesh.render(prog);
   }
}

void loadModel(std::string path)
{
   Assimp::Importer importer;
   const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); 
   if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
   {
      LOG(ERROR) << "Could not load scene at " << path << "," << import.GetErrorString();
      return;
   }
   this->directory = path.substr(0, path.find_last_of('/'));
   this->processNode(scene->mRootNode, scene);
}


void processNode(aiNode * node, const aiScene * scene)
{
   for(GLuint i = 0; i < node->mNumMeshes; i++)
   {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      this->meshes.push_back(this->processMesh(mesh, scene));         
   }
    // Then do the same for each of its children
   for(GLuint i = 0; i < node->mNumChildren; i++)
   {
      this->processNode(node->mChildren[i], scene);
   }
}
