#include "Model.h"
#include "easyLogging++.h"
#include "TextureManager.h"
#include <glm/gtc/type_ptr.hpp>

Model::Model(std::string path):
skelRenderer(skeleton)
{
   loadModel(path);
}
void Model::render(Program & prog)
{
   if(hasSkeleton)
   {
      skeleton.bindAnimatedBones(prog);
   }
   for (std::vector<std::shared_ptr<Mesh> >::iterator mesh = meshes.begin(); mesh != meshes.end(); ++mesh)
   {
      (*mesh)->render(prog);
   }
   if(prog.hasAddedUniform("numDiffuseTextures"))
   {
      prog.getUniform("numDiffuseTextures").bind(0);
   }

   if(prog.hasAddedUniform("numSpecularTextures"))
   {
      prog.getUniform("numSpecularTextures").bind(0);
   }

}

void Model::loadModel(std::string path)
{
   Assimp::Importer importer;
   const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals| aiProcess_FlipUVs);
   if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
   {
      LOG(ERROR) << "Could not load scene at " << path << "," << importer.GetErrorString();
      return;
   }
   this->directory = path.substr(0, path.find_last_of('/'));
   if(scene)
   {
      //Load all bones first.
      this->loadBones(scene->mRootNode);
      this->processNode(scene->mRootNode, scene);
      //Set the binding matricies of the skeleton
      skeleton.finalize();
      skeleton.finalizeAnimation();

      if(skeleton.getNumBones() > 0)
      {
         this->hasSkeleton = true;
      }
      else
      {
         this->hasSkeleton = false;
      }

      for(int anims = 0; anims < scene->mNumAnimations; anims++)
      {
         SkeletalAnimation anim = SkeletalAnimation::importFromAssimp(scene->mAnimations[anims]);
         std::cout << "Adding animation " << anim.getAnimationName() << std::endl;
         animations[anim.getAnimationName()] = anim;
      }
   }



   else ("Could not load mesh at " + path);
}

/**
 * Recursivly load the skeleton for this model.
 * @param node the root node, or a recursive node.
 */
void Model::loadBones(aiNode * node)
{
   skeleton.importBonesFromAssimp(node);
}


void Model::processNode(aiNode * node, const aiScene * scene)
{
   if(node != nullptr)
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
}

std::vector<VertexBoneData> Model::processMeshBoneData(aiMesh * mesh)
{
   std::vector<VertexBoneData> bData;
   bData.resize(mesh->mNumVertices);
   for(int bone = 0; bone < mesh->mNumBones; bone++)
   {
      std::string boneName(mesh->mBones[bone]->mName.data);
      Bone * skelBone = skeleton.getBone(boneName);
      for(int weight = 0; weight < mesh->mBones[bone]->mNumWeights; weight++)
      {
         float boneWeight = mesh->mBones[bone]->mWeights[weight].mWeight;
         float idx = mesh->mBones[bone]->mWeights[weight].mVertexId;
         bData[idx].addBoneData(skelBone->getIndex(),boneWeight);
      }
   }
   return bData;
}
std::shared_ptr<Mesh> Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
   std::vector<Vertex> vertices;
   std::vector<GLuint> indices;
   std::vector<std::shared_ptr<Texture2D>> textures;

   for(GLuint i = 0; i < mesh->mNumVertices; i++)
   {
      Vertex vertex;
      glm::vec3 vector;
      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
      vertex.position = vector;

      glm::vec3 normal;
      normal.x = mesh->mNormals[i].x;
      normal.y = mesh->mNormals[i].y;
      normal.z = mesh->mNormals[i].z;
      vertex.normal = normal;
      if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
      {
         glm::vec2 texCoord;
         texCoord.x = mesh->mTextureCoords[0][i].x;
         texCoord.y = mesh->mTextureCoords[0][i].y;
         vertex.texCoords = texCoord;
      }
      else
      {
         vertex.texCoords = glm::vec2(0.0);
      }
      vertices.push_back(vertex);

   }
   std::vector<VertexBoneData> boneData = processMeshBoneData(mesh);

   std::vector<glm::mat4> boneOffsets;
   boneOffsets.resize(skeleton.getNumBones());
   for(int bone = 0; bone < mesh->mNumBones; bone++)
   {
      std::string boneName(mesh->mBones[bone]->mName.data);
      Bone * skelBone = skeleton.getBone(boneName);
      boneOffsets[skelBone->getIndex()] = glm::transpose(glm::make_mat4(&mesh->mBones[bone]->mOffsetMatrix.a1));
   }

   for(GLuint i = 0; i < mesh->mNumFaces; i++)
   {
      aiFace face = mesh->mFaces[i];
      for(GLuint j = 0; j < face.mNumIndices; j++)
         indices.push_back(face.mIndices[j]);
   }





   aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
   std::vector< std::shared_ptr<Texture2D> > diffuseMaps = this->loadMaterialTextures(material,
      aiTextureType_DIFFUSE, TextureType::DIFFUSE);
   textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());


   std::vector< std::shared_ptr<Texture2D> > specularMaps = this->loadMaterialTextures(material,
      aiTextureType_SPECULAR,TextureType::SPECULAR);
   textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

   return std::shared_ptr<Mesh>(new Mesh(vertices, indices, textures,boneData, boneOffsets));
}


std::vector<std::shared_ptr<Texture2D> > Model::loadMaterialTextures(
      aiMaterial * mat, aiTextureType type,
      TextureType::type texType)
{
   std::vector<std::shared_ptr<Texture2D> > textures;
   for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
   {
      aiString str;
      mat->GetTexture(type, i, &str);
      std::string texString = directory + "/" + std::string(str.C_Str());
      std::shared_ptr<Texture2D> tex = TextureManager::getTexture(texString);
      tex->setTextureType(texType);
      textures.push_back(tex);
   }
   return textures;
}

void Model::renderSkeleton()
{
   skelRenderer.render();
}

void Model::animate(std::string animName, float time)
{
   auto anim = animations.find(animName);
   if(anim != animations.end())
   {
      SkeletalAnimation animation = anim->second;
      float tick = animation.getTickForTime(time);
      const std::vector<SkeletalAnimation::BoneAnimation> & bones = animation.getAnimationData();
      for (std::vector<const SkeletalAnimation::BoneAnimation>::iterator i = bones.begin(); i != bones.end(); ++i)
      {
         Bone * const boneptr  = skeleton.getBone(i->getBoneName());
         if(boneptr != nullptr)
         {
            boneptr->setAnimatedTransform(i->getTransformAtTick(tick).getMatrix());
         }
         else
         {
            LOG(WARNING) << "Could not find bone named " << i->getBoneName();
         }
      }
   }
   else
   {
      LOG(WARNING) << "Could not find animation named " << animName;
   }

   //Update the bone heiearchy after setting all of the animated transforms.
   skeleton.finalizeAnimation();

}
