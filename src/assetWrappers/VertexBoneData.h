#ifndef __VERTEX_BONE_DATA_H__
#define __VERTEX_BONE_DATA_H__
//Global number of bones per vertex
#define NUM_BONES_PER_VERTEX 4
#include <cassert>
#include <easyLogging++.h>
struct VertexBoneData
{

   uint boneIds[NUM_BONES_PER_VERTEX];
   float boneWeights[NUM_BONES_PER_VERTEX];
  
   void addBoneData(int Bone, float weight)
   {
      for(uint i = 0; i < NUM_BONES_PER_VERTEX; i++)
      {
         if(boneWeights[i] == 0.0){
            boneIds[i] = Bone;
            boneWeights[i] = weight;

            return;
         }
      }
      LOG(ERROR) << "Too many bones for a vertex!";
      assert(false); //Too many bones!
   }
   bool isEmpty()
   {
      return boneWeights[0] == 0.0;
   }

};
#endif