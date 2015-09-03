#ifndef __CONTEXT_H__
#define __CONTEXT_H__
#include <glfw/glfw3.h>
class Context
{
   GLFWwindow * window;
   int windowWidth;
   int windowHeight;
public:
   Context(GLFWwindow * window);
   GLFWwindow * getWindow();
   int getWindowWidth();
   int getWindowHeight();

};

#endif
