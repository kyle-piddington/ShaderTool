#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include <assimp/scene.h>
#include "Transform.h"
#include <vector>
class SkeletalAnimation
{
   static int numImported;


public:
   class PositionKeyFrame
   {

      glm::vec3 position;
      float startTime;
      public:
         static PositionKeyFrame interpolate(const PositionKeyFrame & f1, const PositionKeyFrame & f2, float t);

         glm::vec3 getPosition() const
         {
            return position;
         }
         double getStartTime() const
         {
            return startTime;
         }
         PositionKeyFrame(glm::vec3 position, float startTime):
            position(position),
            startTime(startTime){}
   };
   class RotationKeyFrame
   {

      glm::quat rotation;
      float startTime;
      public:
         static RotationKeyFrame interpolate(const RotationKeyFrame & f1, const RotationKeyFrame & f2, float t);

         glm::quat getRotation() const
         {
            return rotation;
         }
         double getStartTime() const
         {
            return startTime;
         }
         RotationKeyFrame(glm::quat rotation, float startTime):
            rotation(rotation),
            startTime(startTime){}
   };
   class ScaleKeyFrame
   {

      glm::vec3 scale;
      float startTime;
      public:
         static ScaleKeyFrame interpolate(const ScaleKeyFrame & f1, const ScaleKeyFrame & f2, float t);

         glm::vec3 getScale() const
         {
            return scale;
         }
         double getStartTime() const
         {
            return startTime;
         }
         ScaleKeyFrame(glm::vec3 scale, float startTime):
            scale(scale),
            startTime(startTime){}
   };

   class BoneAnimation
   {
      friend class SkeletalAnimation;
      std::string boneName;
      std::vector<PositionKeyFrame> posFrames;
      std::vector<RotationKeyFrame> rotFrames;
      std::vector<ScaleKeyFrame> scaleFrames;
      /**
       * Add a frame. Perofrmance degrades if frames are added out of order
       * @param orientation the orientation of the bone
       * @param time        the time of the frame
       */
      void addFrame(PositionKeyFrame pos);
      void addFrame(RotationKeyFrame pos);
      void addFrame(ScaleKeyFrame pos);

      glm::vec3 getTranslationAtTick(float tick) const;
      glm::quat getRotationAtTick(float tick) const;
      glm::vec3 getScaleAtTick(float tick) const;
      
   public:
      
      BoneAnimation(std::string boneName):
         boneName(boneName)
      {
      }

      Transform getTransformAtTick(float time) const;
      std::string getBoneName() const
      {
         return boneName;
      }
   };

    static SkeletalAnimation importFromAssimp(aiAnimation * anim);


    const std::vector<BoneAnimation> & getAnimationData() const
    {
      return boneAnimations;
    }
    float getTickForTime(float t) const; //Convert time to ticks
 

    std::string getAnimationName() const
    {
      return name;
    }
 private:
   std::vector<BoneAnimation> boneAnimations;
   std::string name;
   float tickDuration;
   float ticksPerSecond;

};
#endif