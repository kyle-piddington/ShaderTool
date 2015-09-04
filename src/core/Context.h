#ifndef __CONTEXT_H__
#define __CONTEXT_H__
#include <glfw/glfw3.h>
/**
 * Context provides some basic information about the capabilities and parameters of the GLFW window.
 * Context also provides access to the window if a scene would like to request any more info.
 */
class Context
{
   GLFWwindow * window;
   int windowWidth;
   int windowHeight;
public:
	/**
	 * Create a new context
	 */
   Context(GLFWwindow * window);
   
   /**
    * Get the current GLFW window.
    * @return a pointer to the current GLFW window.
    */
   GLFWwindow * getWindow() const;
   /**
    * Get the current width of the window, in pixels.
    * @return the window width
    */
   int getWindowWidth() const;
   /**
    * Get the current height of the window, in pixels
    * @return the window height.
    */
   int getWindowHeight() const;

};

#endif
