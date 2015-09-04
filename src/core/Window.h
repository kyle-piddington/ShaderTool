#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <glfw/glfw3.h>
#include "Scene.h"
/**
 * Window provides a context for  a scene to run in, and handles the main render loop.
 * Windows manage the state of a current scene, including compilation, reloading, and error handling.
 * They also manage the init, update, and teardown seconds of code. 
 * For all intents and purposes, 99% of an applicaton's lifetime will occur here, in Window.run().
 */
class Window
{
public:
   /**
    * Create a new window
    * @param 	window 	the GLFWwindow to render scenes to.
    */
   Window(GLFWwindow * window);

   /**
    * Deconstruct this window.
    */
   ~Window();
   /**
    * Run the main loop of the scene program. Most of an application's lifetime occurs here.
    */
   void run();
   /**
    * Set the current scene of the window. This method should be called before run(), and never while
    * inside of the run loop.
    * @param 	scene 	the scene to load and display
    */
   void loadScene(Scene * scene);
private:
   Scene * errorScene;
   Scene * currentScene;
   GLFWwindow * currentWindow;

   bool reloadScene = true;

};

#endif
