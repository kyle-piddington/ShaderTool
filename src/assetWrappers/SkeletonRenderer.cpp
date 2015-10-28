#include "SkeletonRenderer.h"

SkeletonRenderer::SkeletonRenderer(Skeleton & skel):
   skeleton(skel)
   {
      skeletonVao.addAttribute(0,skeletonBuffer);
      skeletonVao.addElementArray(indexBfr);

   }
SkeletonRenderer::~SkeletonRenderer()
{

}

void SkeletonRenderer::bindSkeleton()
{
   std::vector<Bone> & bones = skeleton.getAllBones();
   std::vector<glm::vec3> bonePositions;
   bonePositions.resize(bones.size());
   std::vector<unsigned int> indicies;
   indicies.clear();
   for (std::vector<Bone>::iterator i = bones.begin(); i != bones.end(); ++i)
   {
      //Add the position to the array
      
      bonePositions[i->getIndex()] = 
         glm::vec3(i->getAnimMatrix() * i->getOffsetMatrix() * glm::vec4(0.0,0.0,0.0,1.0));

      //Also add the inds if not root.
      if(!i->isRoot())
      {
         indicies.push_back(i->getIndex());
         indicies.push_back(i->getParentIdx());
      }
   }
   skeletonBuffer.setData(bonePositions);
   indexBfr.setData(indicies);

}

void SkeletonRenderer::drawSkeleton()
{
   if(indexBfr.getNumIndicies() > 0)
   {
      skeletonVao.bind();
      glDrawElements(GL_LINES,indexBfr.getNumIndicies(),GL_UNSIGNED_INT,0);
      skeletonVao.unbind();      
   }
   else
   {
      LOG(WARNING) << "No inds for skeletons!";
   }

}

void SkeletonRenderer::render()
{
   bindSkeleton();
   drawSkeleton();
}

