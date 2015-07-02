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
#include "assetWrappers/Texture2d.h"

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
   program.addAttribute("vertTexCoords");
   program.addUniform("tex0");
   program.addUniform("tex1");
   
   GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

   VertexBuffer vbo;
   ElementBufferObject ebo;
   vbo.setData(vertices,36);
   ebo.setData(indices,6);
   VertexArrayObject vao;
   vao.addAttribute(program.getAttribute("position"),vbo, 8 * sizeof(GLfloat));
   vao.addAttribute(program.getAttribute("color"),vbo, 8 * sizeof(GLfloat),  3*sizeof(GLfloat));
   vao.addAttribute(program.getAttribute("vertTexCoords"),vbo, 8 * sizeof(GLfloat),  6*sizeof(GLfloat), 2);
   vao.addElementArray(ebo);
   program.enable();
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   Texture2D boxTexture("assets/textures/container.jpg");
   Texture2D faceTexture("assets/textures/awesomeface.png");
   boxTexture.enable(program.getUniform("tex0"));
   faceTexture.enable(program.getUniform("tex1"));

   while(!glfwWindowShouldClose(window))
   {

      glfwPollEvents();
      glClear(GL_COLOR_BUFFER_BIT);
      
      GLfloat timeValue = glfwGetTime();

      vao.bind();
      glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);
      vao.unbind();
      glfwSwapBuffers(window);

   }
   faceTexture.disable();
   boxTexture.disable();


   /**
    * END TEST CODE
    */

   glfwTerminate();

   return 0;

}