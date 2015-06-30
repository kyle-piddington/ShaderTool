#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <easylogging++.h>
#include "buffers/VertexBuffer.h"
#include "glsl/Program.h"
#include "logger/GL_Logger.h"
#include "buffers/VertexBuffer.h"
#include "buffers/VertexArrayObject.h"
#include "buffers/ElementBufferObject.h"
INITIALIZE_EASYLOGGINGPP

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
   if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
   {
      glfwSetWindowShouldClose(window, GL_TRUE);
   }
}

int main()
{
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
   glViewport(0,0,800,600);
   GL_Logger::LogError("Error in setup", glGetError());


   glewExperimental = GL_TRUE;
   if(glewInit() != GLEW_OK)
   {
      std::cout << "Failed to initialize GLEW" << std::endl;
      return -1;
   }
   GL_Logger::LogError("Error in GLEW startup (Safe to ignore)", glGetError());
   glfwSetKeyCallback(window, key_callback);


   /**
    * TEST CODE
    */
   Program program("Test Program");
   program.addVertexShader("assets/shaders/test_vert.vs");
   program.addFragmentShader("assets/shaders/test_frag.fs");
   program.create();

   program.addAttribute("position");
   program.addAttribute("color");
   program.addUniform("offset");
   
   GLfloat vertices[] = {
    // Positions         // Colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom Right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom Left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Top 
   };
   GLuint indices[] = {  // Note that we start from 0!
      0, 1, 2
   };

   VertexBuffer vbo;
   ElementBufferObject ebo;
   vbo.setData(vertices,24);
   ebo.setData(indices,3);
   VertexArrayObject vao;
   vao.addAttribute(program.getAttribute("position"),vbo, 6 * sizeof(GLfloat));
   vao.addAttribute(program.getAttribute("color"),vbo, 6 * sizeof(GLfloat),  3*sizeof(GLfloat));
   vao.addElementArray(ebo);
   program.enable();
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


   while(!glfwWindowShouldClose(window))
   {

      glfwPollEvents();
      glClear(GL_COLOR_BUFFER_BIT);
      
      GLfloat timeValue = glfwGetTime();
      glUniform3f(program.getUniform("offset"),cos(timeValue),sin(timeValue),0);

      vao.bind();
      glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);
      vao.unbind();
      glfwSwapBuffers(window);

   }


   /**
    * END TEST CODE
    */

   glfwTerminate();

   return 0;

}