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
 // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Left  
         0.5f, -0.5f, 0.0f, // Right 
         0.0f,  0.5f, 0.0f  // Top   
    };
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


   while(!glfwWindowShouldClose(window))
   {
      glfwPollEvents();
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      program.enable();
   
      
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);

      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(window);
   }


   /**
    * END TEST CODE
    */

   glfwTerminate();

   return 0;

}