#include "GLFWHandler.h"
#include "Keyboard.h"
void  GLFWHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
   if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
   {
      glfwSetWindowShouldClose(window, GL_TRUE);
   }
   Keyboard::setKeyStatus(key,action);
   //Can do more loggging or updating here.
}
