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
float pitch = 0;
float yaw = 0;



void handleCameraInput(Camera & camera)
{
   const float Cam_Speed = 1.0/30.0;
   const float Cam_Rot_Speed = M_PI;
   glm::vec3 translate(0.0);
   glm::vec3 rotate(0.0);
   if(Keyboard::isKeyDown(GLFW_KEY_W))
   {
      translate += camera.transform.forward() * Cam_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_S))
   {
      translate -= camera.transform.forward() * Cam_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_A))
   {
      translate-= camera.transform.right() * Cam_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_D))
   {
      translate+= camera.transform.right() * Cam_Speed;
   }

   rotate.x = (Mouse::getLastY() - Mouse::getY())/screenHeight/2.0 * Cam_Rot_Speed;
   rotate.y = (Mouse::getLastX() - Mouse::getX())/screenHeight/2.0 * Cam_Rot_Speed;
   pitch += rotate.x;
   yaw += rotate.y;
   rotate.z = 0;
   camera.translate(translate);
   camera.setRotation(glm::vec3(pitch,yaw,0));
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
   program.addVertexShader("assets/shaders/debug_vert.vs");
   program.addFragmentShader("assets/shaders/basic_color_frag.fs");
   program.create();

   Program lampProg("Debug Light Program");
   lampProg.addVertexShader("assets/shaders/debug_vert.vs");
   lampProg.addFragmentShader("assets/shaders/debug_frag.fs");
   lampProg.create();
   /**
    * Add program introspection to gether attribute names and uniforms later.
    */
   program.addAttribute("position");
   program.addUniform("M");
   program.addUniform("V");
   program.addUniform("P");
   program.addUniform("objColor");
   program.addUniform("lightColor");


   lampProg.addAttribute("position");
   lampProg.addUniform("M");
   lampProg.addUniform("V");
   lampProg.addUniform("P");
   /*
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
   */
   GLfloat lightVertices[]
   {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
   };

   VertexBuffer vbo;
   ElementBufferObject ebo;
   vbo.setData(lightVertices,36*3);
   //ebo.setData(indices,6);
   VertexArrayObject vao;
   vao.addAttribute(program.getAttribute("position"),vbo);

   VertexArrayObject lightVAO;
   lightVAO.addAttribute(program.getAttribute("position"),vbo);

   //vao.addElementArray(ebo);
   glm::mat4 M;
   glm::mat4 V;
   glm::mat4 P;
   P = glm::perspective(45.0f, screenWidth / screenHeight, 0.1f, 100.0f);

   lampProg.enable();
   glUniformMatrix4fv(lampProg.getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));
   GL_Logger::LogError("Could not set uniform perspective 2", glGetError());
   
   program.enable();
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

   
   glUniformMatrix4fv(program.getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));
   GL_Logger::LogError("Could not set uniform perspective 1", glGetError());
   glUniform3f(program.getUniform("objColor"), 1.0f, 0.5f, 0.31f);
   glUniform3f(program.getUniform("lightColor"),  1.0f, 1.0f, 1.0f); // Also set light's color (white)

   
   Transform cubeTransform, lightTransform;
   glm::vec3 cubePos(0.0f,  0.0f,  0.0f);
   glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
   cubeTransform.setPosition(cubePos);
   lightTransform.setPosition(lightPos);
   lightTransform.setScale(glm::vec3(0.2));
   
   glEnable(GL_DEPTH_TEST);
   camera.setPosition(glm::vec3(0,0,5));
   while(!glfwWindowShouldClose(window))
   {

      glfwPollEvents();
      GLFWHandler::update();
      handleCameraInput(camera);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      vao.bind();
      program.enable();
      V = camera.getViewMatrix();
      glUniformMatrix4fv(program.getUniform("V"), 1, GL_FALSE, glm::value_ptr(V));
      
      M = cubeTransform.getMatrix();
      glUniformMatrix4fv(program.getUniform("M"), 1, GL_FALSE, glm::value_ptr(M));
      glDrawArrays(GL_TRIANGLES,0,36);
      
      //Draw lamp
      
      lampProg.enable();
      lightVAO.bind();
      M = lightTransform.getMatrix();
      glUniformMatrix4fv(lampProg.getUniform("V"), 1, GL_FALSE, glm::value_ptr(V));
      glUniformMatrix4fv(lampProg.getUniform("M"), 1, GL_FALSE, glm::value_ptr(M));
      glDrawArrays(GL_TRIANGLES,0,36);
      lampProg.disable();
      
      



      lightVAO.unbind();
      
      glfwSwapBuffers(window);

   }


   /**
    * END TEST CODE
    */

   glfwTerminate();

   return 0;

}