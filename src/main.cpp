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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "util/Camera.h"
#include "io/Keyboard.h"
#include "io/GLFWHandler.h"
#include "io/Mouse.h"
#include "Transform.h"

INITIALIZE_EASYLOGGINGPP


const float screenWidth =800.0;
const float screenHeight = 600.0;




void mouseCallback(GLFWwindow * window, double x, double y)
{
   
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
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);
   Camera camera((float)width, (float)height);
   glViewport(0, 0, width, height);
   GL_Logger::LogError("Error in setup", glGetError());


   glewExperimental = GL_TRUE;
   if(glewInit() != GLEW_OK)
   {
      std::cout << "Failed to initialize GLEW" << std::endl;
      return -1;
   }
   GL_Logger::LogError("Error in GLEW startup (Safe to ignore)", glGetError());
   glfwSetKeyCallback(window, GLFWHandler::key_callback);
   glfwSetCursorPosCallback(window, GLFWHandler::mousePositionCallback);
   

   /**
    * TEST CODE
    */

   Program program("Test Program");
   program.addVertexShader("assets/shaders/test_vert.vs");
   program.addFragmentShader("assets/shaders/test_frag.fs");
   program.create();

   /**
    * Add program introspection to gether attribute names and uniforms later.
    */
   program.addAttribute("position");
   program.addAttribute("vertTexCoords");
   program.addUniform("tex0");
   program.addUniform("tex1");
   program.addUniform("M");
   program.addUniform("V");
   program.addUniform("P");
   GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

   VertexBuffer vbo;
   ElementBufferObject ebo;
   vbo.setData(vertices,36*5);
   //ebo.setData(indices,6);
   VertexArrayObject vao;
   vao.addAttribute(program.getAttribute("position"),vbo, 5 * sizeof(GLfloat));
   vao.addAttribute(program.getAttribute("vertTexCoords"),vbo, 5 * sizeof(GLfloat),  3*sizeof(GLfloat), 2);
   //vao.addElementArray(ebo);
   program.enable();
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

   glm::mat4 M;
   glm::mat4 V;
   glm::mat4 P;
   V = glm::translate(V, glm::vec3(0.0f, 0.0f, -3.0f));
   P = glm::perspective(45.0f, screenWidth / screenHeight, 0.1f, 100.0f);

   glUniformMatrix4fv(program.getUniform("P"), 1, GL_FALSE, glm::value_ptr(camera.getPerspectiveMatrix()));



   Texture2D boxTexture("assets/textures/container.jpg");
   Texture2D faceTexture("assets/textures/awesomeface.png");
   boxTexture.enable(program.getUniform("tex0"));
   faceTexture.enable(program.getUniform("tex1"));
   Transform testTransform;
   glm::vec3 cubePositions[] = {
     glm::vec3( 0.0f,  0.0f,  0.0f),
     glm::vec3( 2.0f,  5.0f, -15.0f),
     glm::vec3(-1.5f, -2.2f, -2.5f),
     glm::vec3(-3.8f, -2.0f, -12.3f),
     glm::vec3( 2.4f, -0.4f, -3.5f),
     glm::vec3(-1.7f,  3.0f, -7.5f),
     glm::vec3( 1.3f, -2.0f, -2.5f),
     glm::vec3( 1.5f,  2.0f, -2.5f),
     glm::vec3( 1.5f,  0.2f, -1.5f),
     glm::vec3(-1.3f,  1.0f, -1.5f)
   };


   glEnable(GL_DEPTH_TEST);
   GLfloat theta = 0;
   GLfloat phi = 0;
   while(!glfwWindowShouldClose(window))
   {

      glfwPollEvents();
      GLFWHandler::update();
      double mouseX = (Mouse::getX()-screenWidth/2)/(screenWidth/4);
      double mouseY = -(Mouse::getY()-screenHeight/2)/(screenHeight/4);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      vao.bind();

      if(Keyboard::isKeyDown(GLFW_KEY_A))
      {
        theta += 1/60.0;

      }
      if(Keyboard::isKeyDown(GLFW_KEY_D))
      {
        theta -= 1/60.0;

      }
      if(Keyboard::isKeyDown(GLFW_KEY_W))
      {
        phi += 1/60.0;

      }
      if(Keyboard::key(GLFW_KEY_S))
      {
        phi -= 1/60.0;
      }
      camera.setPosition(glm::vec3(0,cos(phi),5));
      camera.lookAt(glm::vec3(0.0));

      glUniformMatrix4fv(program.getUniform("V"),1,GL_FALSE,glm::value_ptr(camera.getViewMatrix()));
      for(int i = 0; i < 10; i++)
      {
         M = glm::translate(glm::mat4(),cubePositions[i]);
         testTransform.setPosition(cubePositions[i]);
         testTransform.lookAt(glm::vec3(mouseX,mouseY,5));
         M=testTransform.getMatrix();
         /*
         float angle = 20.0f * i;
         M = glm::rotate(M, ((GLfloat)glfwGetTime() * 0.5f * (i%3 == 0)) + angle, glm::vec3(1.0f, 0.3f, 0.5f));
         */
         glUniformMatrix4fv(program.getUniform("M"), 1, GL_FALSE, glm::value_ptr(M));
         glDrawArrays(GL_TRIANGLES,0,36);


      }



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