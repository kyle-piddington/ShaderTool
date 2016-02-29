#include "GLFWHandler.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

void  GLFWHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{


   if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
   {
      glfwSetWindowShouldClose(window, GL_TRUE);
   }
   /**
    * Allow Imgui to consume the event
    */
   if(ImGui::IsWindowFocused() || ImGui::IsMouseHoveringAnyWindow())
   {
      ImGui_ImplGlfwGL3_KeyCallback(window,key,scancode,action,mode);
   }
   else
   {
      Keyboard::setKeyStatus(key,action);
   }

   //Can do more loggging or updating here.
}

void GLFWHandler::mousePositionCallback(GLFWwindow * window, double x, double y)
{
   Mouse::updateMousePos(x,y);
}

void GLFWHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
   //Imgui event capture
   //Can't select a window without actually hovering

   if(ImGui::IsWindowFocused() || ImGui::IsMouseHoveringAnyWindow())
   {
      ImGui_ImplGlfwGL3_MouseButtonCallback(window,button,action,mods);
   }
   else
   {
      Mouse::setButtonStatus(button,action);

   }

}


void GLFWHandler::scrollWheelCallback(GLFWwindow * window, double xOffset, double yOffset)
{
   if(ImGui::IsWindowFocused() || ImGui::IsMouseHoveringAnyWindow())
   {
      ImGui_ImplGlfwGL3_ScrollCallback(window,xOffset,yOffset);
   }
   else
   {
      Mouse::setScrollStatus(xOffset, yOffset);
   }
}

void GLFWHandler::characterCallback(GLFWwindow * window, unsigned int c)
{
   ImGui_ImplGlfwGL3_CharCallback(window, c);
}




void GLFWHandler::update()
{
   Keyboard::update();
   Mouse::update();
}

