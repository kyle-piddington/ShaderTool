#include "Skeleton.h"

Bone::Bone(std::string name, int boneIdx, glm::mat4 offsetTransform):
name(name),
offsetTransform(offsetTransform),
localAnimTransform(1.0),
bindTransform(offsetTransform),
animTransform(1.0),
idx(boneIdx),
parentBoneIdx(-1)
{

}


void Bone::setAnimatedTransform(glm::mat4 animTransform)
{
   this->localAnimTransform = animTransform;
}

void Bone::setParent(int parentBoneIdx)
{
   this->parentBoneIdx = parentBoneIdx;
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
            int pIdx = boneMap[(heiarchy[i->name])];
            i->setParent(pIdx);
         }
      }
      i->setAnimatedTransform(i->offsetTransform);
   }

   // for (std::vector<Bone>::iterator i = bones.begin(); i != bones.end(); ++i)
   // {
   //    glm::mat4 parentMtx(1.0);
   //    if(!i->isRoot())
   //    {
   //       Bone parent = bones[i->parentBoneIdx];
   //       //Recurse up the hiearchy and generate the final bind matrix
   //       while(!parent.isRoot())
   //       {
   //          parentMtx = parent.offsetTransform * parentMtx;
   //          parent = bones[parent.parentBoneIdx];
   //       }
   //    }
   //    i->bindTransform = parentMtx * i->offsetTransform;
   // }
}

void Skeleton::finalizeAnimation()
{
   for (std::vector<Bone>::iterator i = bones.begin(); i != bones.end(); ++i)
   {
      glm::mat4 parentMtx(1.0);
      if(!i->isRoot())
      {
         Bone parent = bones[i->parentBoneIdx];
         //Recurse up the hiearchy and generate the final bind matrix
         while(!parent.isRoot())
         {
            parentMtx = parent.localAnimTransform * parentMtx;
            parent = bones[parent.parentBoneIdx];
         }
      }
      i->animTransform = parentMtx * i->localAnimTransform;
   }
}

void Skeleton::bindPose(Program * prog)
{

}
void Skeleton::bindAnimatedBones(Program * prog)
{

}


