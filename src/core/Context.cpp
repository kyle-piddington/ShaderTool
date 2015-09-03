#include "Context.h"

Context::Context(GLFWwindow * window):
window(window)
{
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
}

GLFWwindow * Context::getWindow()
{
   return window;
}
int Context::getWindowWidth()
{
   return windowWidth;
}
int Context::getWindowHeight()
{
   return windowHeight;
}
