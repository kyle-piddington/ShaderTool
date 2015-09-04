#ifndef __WORLD_H__
#define __WORLD_H__ 
#include <glm/glm.hpp>
/**
 * Currently, World provides a global Axis of Up, Right, and Forward for the rest of the application to use
 * More may be added here later!
 */
struct World
{
   static const glm::vec3 Up;
   static const glm::vec3 Right;
   static const glm::vec3 Forward;
     
};
#endif