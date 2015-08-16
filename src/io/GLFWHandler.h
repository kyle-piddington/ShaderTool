#ifndef __GLFW_HANDLER_H__
#define __GLFW_HANDLER_H__

#include <GLFW/glfw3.h>
/**
 * Includes GLFW callback functions, forwards events to other parts of app
 */

struct GLFWHandler
{
   static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
   static void mousePositionCallback(GLFWwindow * window, double x, double y);
   static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
   static void update();
};



#endif