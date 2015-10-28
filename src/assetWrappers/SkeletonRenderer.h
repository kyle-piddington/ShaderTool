#ifndef __SKELETON_RENDERER_H__
#define __SKELETON_RENDERER_H__
#include "VertexArrayObject.h"
#include "Skeleton.h"

class SkeletonRenderer
{
private:
   Skeleton & skeleton;
   void bindSkeleton();
   void drawSkeleton();
public:
   SkeletonRenderer(Skeleton & skel);
   ~SkeletonRenderer();
   //Render the skeleton as lines.
   
   void render();

   VertexBuffer skeletonBuffer;
   ElementBufferObject indexBfr;

   VertexArrayObject skeletonVao;



};
#endif