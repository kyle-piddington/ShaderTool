#include "Context.h"

Context::Context(GLFWwindow * window):
window(window)
{
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
}

GLFWwindow * Context::getWindow() const
{
   return window;
}
int Context::getWindowWidth() const
{
   return windowWidth;
}
int Context::getWindowHeight() const
{
   return windowHeight;
}
