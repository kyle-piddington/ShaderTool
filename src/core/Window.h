#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <glfw/glfw3.h>
#include "Scene.h"
class Window
{
public:
   Window(GLFWwindow * window);
   ~Window();
   void run();
   void loadScene(Scene * scene);
private:
   Scene * errorScene;
   Scene * currentScene;
   GLFWwindow * currentWindow;

   bool reloadScene = true;

};

#endif
