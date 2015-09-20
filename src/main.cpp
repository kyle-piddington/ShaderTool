#define GLEW_STATIC
#include <GL/glew.h>
#include <easylogging++.h>
#include "Window.h"
#include "EmptyScene.h"
#include "GLFWHandler.h"
#include "ReloadLocator.h"
#include "AppleLiveReloadManager.h"
#include "GL_Logger.h"
#include <GLFW/glfw3.h>
#include "ErrorScene.h"
#include "BoxScene.h"
#include "AssimpScene.h"
#include "OutlineScene.h"
#include "BlendingScene.h"
#include "PostProcessScene.h"
#include "CubemapScene.h"
INITIALIZE_EASYLOGGINGPP

int main()
{
   /**
    * Setup the current environment
    */
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
   GLFWwindow * window = glfwCreateWindow(800,600, "LearnOpenGL", nullptr, nullptr);

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

   glfwSetKeyCallback(window, GLFWHandler::key_callback);
   glfwSetCursorPosCallback(window, GLFWHandler::mousePositionCallback);
   glfwSetMouseButtonCallback(window, GLFWHandler::mouseButtonCallback);

   FileSystem::ReloadLocator::Initialize();
   FileSystem::ReloadLocator::provide(new AppleReloadManager());


   Context * ctx = new Context(window);
   //Init scene of choice here
   Scene * scene = new PostProcessScene(ctx);
   scene->setContext(ctx);

   //Create a window for the program to run in
   Window renderWindow(window);

   renderWindow.loadScene(scene);
   renderWindow.run();

   delete scene;
   delete ctx;
   return 0;
}