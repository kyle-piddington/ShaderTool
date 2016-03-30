#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <easylogging++.h>

#define CATCH_CONFIG_RUNNER
#include "ReloadLocator.h"
#include "catch/catch.hpp"
#include "GL_Logger.h"



INITIALIZE_EASYLOGGINGPP


int main( int argc, char*  argv[] )
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
   GLFWwindow * window = glfwCreateWindow(800,600, "CDTI Display", nullptr, nullptr);

   if (window == nullptr)
   {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);
   glViewport(0, 0, width, height);

   glewExperimental = GL_TRUE;
   if(glewInit() != GLEW_OK)
   {
      std::cout << "Failed to initialize GLEW" << std::endl;
      return -1;
   }
   GL_Logger::LogError("Error in GLEW startup (Safe to ignore)", glGetError());
   FileSystem::ReloadLocator::Initialize();

  int result = Catch::Session().run( argc, argv );

  // global clean-up...

  return result;
}
