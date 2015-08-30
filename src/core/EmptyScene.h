#ifndef __EMPTY_SCENE_H__
#define __EMPTY_SCENE_H__

#include "Scene.h"
/**
 * A scene starting point with no gemoetry, no initialization
 * and empty implementations of Scene's virtual methods
 */
class EmptyScene : public Scene
{
public:
   EmptyScene();
   virtual ~EmptyScene();
   /**
    * Initialize the programs needed by this scene.
    * Programs should be created here for cleanliness.
    */
   virtual void initPrograms();

   /**
    * Bind an initial set of data to the scene. This function is called once 
    * per loading of the scene.
    */
   virtual void initialBind();

   /**
    * Render the scene. this function is called every frame
    */
   virtual void render();
   /**
    * Update the scene. this function is called every frame
    */
   virtual void update();
   
   virtual void cleanup();
 
private:

};
#endif