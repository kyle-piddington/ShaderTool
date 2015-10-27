#ifndef __SKELETON_H__
#define __SKELETON_H__
#include "Transform.h"
#include "Program.h"
#include <unordered_map>
#include <vector>
#include <easyLogging++.h>
/**
 * A Skeleton for a model, used in animation.
 */
class Bone{
   private:
      friend class Skeleton;
      //Consider inverse heierchy
      //Raw ptr since skeleton handles allocation of bones
      Bone * parentBone;
      glm::mat4 offsetTransform;
      glm::mat4 bindTransform;
      glm::mat4 animTransform;
      std::string name;
      int idx;
      Bone(std::string name, int boneIdx,glm::mat4 offsetTransform);


      glm::mat4 getBindMatrix()
      {
         return bindTransform;
      }
      glm::mat4 getAnimMatrix()
      {
         return animTransform;
      }
      void setParent(Bone * const bone);
      bool isRoot()
      {
         return parentBone != nullptr;
      }
   public:
      void setAnimatedTransform(glm::mat4 animTransform);

      int getIndex()
      {
         return idx;
      }

};
class Skeleton
{
   std::vector<Bone> bones;
   //Child->parent map for bone heiarchy
   std::unordered_map<std::string, std::string> heiarchy;
   std::unordered_map<std::string,int> boneMap;

public:
   Skeleton();
   ~Skeleton();

   //This is awful, refactor to use better shared_ptr's later.
   Bone * const getBone(std::string boneName);
   void addBone(std::string boneName, glm::mat4 boneMtx, std::string parent);
   /**
    * Commit all parent->child relationshps and pre-multiply the bind matricies.
    * Animation matricies will require a re-multiplication every update.
    */
   void finalize();

   /**
    * Bind the default pose.
    * By default, also bind the identiy matrix into the animation slot.
    * @param prog [description]
    */
   void bindPose(Program * prog);

   void bindAnimatedBones(Program * prog);


};
#endif