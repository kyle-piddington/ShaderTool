#include "Skeleton.h"

Bone::Bone(std::string name, int boneIdx, glm::mat4 offsetTransform):
name(name),
offsetTransform(offsetTransform),
bindTransform(offsetTransform),
animTransform(1.0),
idx(boneIdx),
parentBone(nullptr)
{

}


void Bone::setAnimatedTransform(glm::mat4 animTransform)
{

}

void Bone::setParent(Bone * const parent)
{
   this->parentBone = parent;
}

Skeleton::Skeleton()
{

}
Skeleton::~Skeleton()
{
   
}

Bone * const Skeleton::getBone(std::string boneName)
{
   auto boneId = boneMap.find(boneName);
   if(boneId == boneMap.end())
   {
      LOG(ERROR) << "No Bone named " << boneName << "In skeleton!";
      return nullptr;
   }
   else
   {
      return &bones[boneId->second];
   }
}


void Skeleton::addBone(std::string boneName, glm::mat4 boneMtx, std::string parentName)
{
   heiarchy[boneName] = parentName;
   Bone bone(boneName,bones.size(),boneMtx);
   boneMap[boneName] = bone.getIndex();
   bones.push_back(bone);

}



void Skeleton::finalize()
{
   for (std::vector<Bone>::iterator i = bones.begin(); i != bones.end(); ++i)
   {
      if(i->name != "")
      {
         if(heiarchy[i->name] != "")
         {
            i->setParent(getBone(heiarchy[i->name]));
         }
      }
   }
   for (std::vector<Bone>::iterator i = bones.begin(); i != bones.end(); ++i)
   {
      glm::mat4 parentMtx(1.0);
      Bone *parent = i->parentBone;
      //Recurse up the hiearchy and generate the final bind matrix
      while(parent && !parent->isRoot())
      {
         parentMtx *= parent->offsetTransform;
         parent = parent->parentBone;
      }
      i->bindTransform = parentMtx * i->offsetTransform;
   }
}

void Skeleton::bindPose(Program * prog)
{

}
void Skeleton::bindAnimatedBones(Program * prog)
{

}


