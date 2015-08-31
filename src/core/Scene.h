#ifndef __SCENE_H__
#define __SCENE_H__

#include "Program.h"

class Scene
{
public:
   Scene();
   virtual ~Scene();
   /**
    * Initialize the programs needed by this scene.
    * Programs should be created here, to allow the scene
    * to track dependencies
    */
   virtual void initPrograms() = 0;

   /**
    * Bind an initial set of data to the scene. This function is called once 
    * per loading of the scene.
    */
   virtual void initialBind() = 0;

   /**
    * Render the scene. this function is called every frame
    */
   virtual void render() = 0;
   /**
    * Update the scene. this function is called every frame
    */
   virtual void update() = 0;
   
   /**
    * Cleanup the scene before destroying data. This function is called on a shader error, or before 
    * changing scenes.
    */
   virtual void cleanup();
   /**
    * Check to see if the scene can be rendered;
    * @return true if all programs are OK, and ready to go
    */
   bool canRenderScene();

   /**
    * See if the scene should reload any of it's programs
    * @return true if the scene should be reloaded.
    */
   bool shouldReloadScene();

   /**
    * Compile the current required programs
    * @return true if there were no issues compiling
    */
   bool compilePrograms();
  
   /**
    * Add a new program to the scene.
    * @param  programName The program to create
    * @return             a pointer to the program.
    */
   Program * createProgram(std::string programName);

private:

   std::vector<Program *> requiredPrograms;

};
#endif