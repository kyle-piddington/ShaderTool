#ifndef __SKELETON_H__
#define __SKELETON_H__
#include "Transform.h"
#include "Program.h"
#include <unordered_map>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <easyLogging++.h>
/**
 * A Skeleton for a model, used in animation.
 */
class Bone{
   private:
     
      friend class Skeleton;
      //Consider inverse heierchy
      //Raw ptr since skeleton handles allocation of bones
      int parentBoneIdx;
      glm::mat4 offsetTransform;
      glm::mat4 localAnimTransform;
      glm::mat4 bindTransform;
      glm::mat4 animTransform;

      std::string name;
      int idx;
      Bone(std::string name, int boneIdx,glm::mat4 offsetTransform);


    
      void setParent(int parentBoneIdx);
      
      public:
      void setAnimatedTransform(glm::mat4 animTransform);

      int getIndex()
      {
         return idx;
      }

      glm::mat4 getBindMatrix()
      {
         return bindTransform;
      }
      glm::mat4 getOffsetMatrix()
      {
         return offsetTransform;
      }
      glm::mat4 getAnimMatrix()
      {
         return animTransform;
      }
      bool isRoot()
      {
         return parentBoneIdx == -1;
      }
      int getParentIdx()
      {
         return parentBoneIdx;
      }
      std::string getName()
      {
         return name;
      }


};
class Skeleton
{
   struct BoneTreeNode
   {
      int boneIdx;
      std::vector<BoneTreeNode> children;
   };

   std::vector<Bone> bones;
   //Child->parent map for bone heiarchy
   BoneTreeNode  boneRoot;
   glm::mat4 rootInverseTransform;
   std::unordered_map<std::string,int> boneMap;
   void finalize(BoneTreeNode & node, int pIdx);
   void importBonesFromAssimp(aiNode * node, BoneTreeNode & parent);
   void finalizeAnimation(BoneTreeNode & node, glm::mat4 parentMtx);

public:
   Skeleton();
   ~Skeleton();

   //This is awful, refactor to use better shared_ptr's later.
   Bone * const getBone(std::string boneName);

   //Load bones into the skeleton
   void importBonesFromAssimp(aiNode * node);

   /**
    * Add a bone to the skeleton
    * @param  boneName name of the bone
    * @param  boneMtx  offset matrix
    * @return          index
    */
   int addBone(std::string boneName, glm::mat4 boneMtx);

   int getNumBones();
   /**
    * Commit all parent->child relationshps and pre-multiply the bind matricies.
    * Animation matricies will require a re-multiplication every update.
    */
   void finalize();


   /**
    * Update all animated transforms
    */
    void finalizeAnimation();
   /**
    * Bind the default pose.
    * By default, also bind the identiy matrix into the animation slot.
    * @param prog [description]
    */
   void bindPose(Program * prog);

   void bindAnimatedBones(Program & prog);

   /**
    * Get all the bones
    */
   std::vector<Bone> & getAllBones()
   {
      return bones;
   }


};
#endif