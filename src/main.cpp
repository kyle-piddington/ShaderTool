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
#include "Material.h"
#include "Light.h"

INITIALIZE_EASYLOGGINGPP


const float screenWidth =800.0;
const float screenHeight = 600.0;
float pitch = 0;
float yaw = 0;

glm::mat3 createNormalMatrix(const glm::mat4 & view, const glm::mat4 & model)
{
   return glm::mat3(glm::transpose(glm::inverse(view * model)));
}

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
   if(Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT))
   {
      rotate.x = (Mouse::getLastY() - Mouse::getY())/screenHeight/2.0 * Cam_Rot_Speed;
      rotate.y = (Mouse::getLastX() - Mouse::getX())/screenHeight/2.0 * Cam_Rot_Speed;
      pitch += rotate.x;
      yaw += rotate.y;
      rotate.z = 0;
   }
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
   glfwSetMouseButtonCallback(window, GLFWHandler::mouseButtonCallback);


   /**
    * TEST CODE
    */
   bool programsOK = true;
   Program phongProg("Test Program");
   phongProg.addVertexShader("assets/shaders/phong_vert.vs");
   phongProg.addFragmentShader("assets/shaders/phong_frag.fs");
   programsOK &= (phongProg.create() >= 0);

   Program lampProg("Debug Light Program");
   lampProg.addVertexShader("assets/shaders/debug_vert.vs");
   lampProg.addFragmentShader("assets/shaders/debug_frag.fs");
   programsOK &= (lampProg.create() >= 0);
   /**
    * Add program introspection to gether attribute names and uniforms later.
    */
   phongProg.addAttribute("position");
   phongProg.addAttribute("normal");

   phongProg.addUniform("M");
   phongProg.addUniform("V");
   phongProg.addUniform("P");
   phongProg.addUniform("N");
   phongProg.addUniform("material.ambient");
   phongProg.addUniform("material.diffuse");
   phongProg.addUniform("material.specular");
   phongProg.addUniform("material.shininess");
   phongProg.addUniform("light.position");
   phongProg.addUniform("light.ambient");
   phongProg.addUniform("light.diffuse");
   phongProg.addUniform("light.specular");

   Material cubeMaterial(
      glm::vec3(1.0,0.5,0.31),
      glm::vec3(1.0,0.5,0.31),
      glm::vec3(0.5),
      32.0f);

   Light lamp(
      glm::vec3(0.2),
      glm::vec3(0.5),
      glm::vec3(1.0));

   lampProg.addAttribute("position");
   lampProg.addUniform("M");
   lampProg.addUniform("V");
   lampProg.addUniform("P");
   lampProg.addUniform("debugColor");

   GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
   };


   VertexBuffer vbo;
   ElementBufferObject ebo;
   vbo.setData(vertices,36*6);
   //ebo.setData(indices,6);
   VertexArrayObject vao;
   vao.addAttribute(phongProg.getAttribute("position"),vbo,6*sizeof(GLfloat));
   vao.addAttribute(phongProg.getAttribute("normal"),vbo,6*sizeof(GLfloat),3*sizeof(GLfloat));

   VertexArrayObject lightVAO;
   lightVAO.addAttribute(phongProg.getAttribute("position"),vbo, 6*sizeof(GLfloat));

   //vao.addElementArray(ebo);
   glm::mat4 M;
   glm::mat4 V;
   glm::mat4 P;
   glm::mat3 NORM;
   P = glm::perspective(45.0f, screenWidth / screenHeight, 0.1f, 100.0f);

   lampProg.enable();
   glUniformMatrix4fv(lampProg.getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));
   GL_Logger::LogError("Could not set uniform perspective 2", glGetError());

   phongProg.enable();
   glClearColor(0.2f, 0.2f, 0.2f, 1.0f);


   glUniformMatrix4fv(phongProg.getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));
   GL_Logger::LogError("Could not set uniform perspective 1", glGetError());
   cubeMaterial.bind(
         phongProg.getUniform("material.ambient"),
         phongProg.getUniform("material.diffuse"),
         phongProg.getUniform("material.specular"),
         phongProg.getUniform("material.shininess")
         );
   Transform cubeTransform;
   glm::vec3 cubePos(0.0f,  0.0f,  0.0f);
   glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
   cubeTransform.setPosition(cubePos);
   lamp.transform.setPosition(lightPos);
   lamp.transform.setScale(glm::vec3(0.2));

   glEnable(GL_DEPTH_TEST);
   camera.setPosition(glm::vec3(0,0,5));
   while(!glfwWindowShouldClose(window) && programsOK)
   {

      glfwPollEvents();
      GLFWHandler::update();
      handleCameraInput(camera);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      vao.bind();
      phongProg.enable();
      V = camera.getViewMatrix();
      glUniformMatrix4fv(phongProg.getUniform("V"), 1, GL_FALSE, glm::value_ptr(V));

      M = cubeTransform.getMatrix();
      NORM = createNormalMatrix(V, M);
      
      lamp.bind(
         phongProg.getUniform("light.position"),
         phongProg.getUniform("light.ambient"),
         phongProg.getUniform("light.diffuse"),
         phongProg.getUniform("light.specular"));

      glUniformMatrix3fv(phongProg.getUniform("N"), 1, GL_FALSE, glm::value_ptr(NORM));
      glUniformMatrix4fv(phongProg.getUniform("M"), 1, GL_FALSE, glm::value_ptr(M));
      glDrawArrays(GL_TRIANGLES,0,36);

      //Draw lamp

      lampProg.enable();
      lightVAO.bind();
      M = lamp.transform.getMatrix();
      glUniformMatrix4fv(lampProg.getUniform("V"), 1, GL_FALSE, glm::value_ptr(V));
      glUniformMatrix4fv(lampProg.getUniform("M"), 1, GL_FALSE, glm::value_ptr(M));
      glUniform3fv(lampProg.getUniform("debugColor"),1,glm::value_ptr(lamp.diffuse));
      glDrawArrays(GL_TRIANGLES,0,36);
      lampProg.disable();

      lightVAO.unbind();

      //Update lamp
      lamp.transform.setPosition(
         glm::vec3(2*cos(glfwGetTime()), cos(0.5*glfwGetTime()), 2*sin(glfwGetTime())));
      lamp.transform.lookAt(cubeTransform.getPosition());
      glm::vec3 lightColor;
      lightColor.x = fabs(sin(glfwGetTime() * 2.0f)) + 0.2f;
      lightColor.y = fabs(sin(glfwGetTime() * 0.7f)) + 0.2f;
      lightColor.z = fabs(sin(glfwGetTime() * 1.3f)) + 0.2f;
      lamp.diffuse = lightColor * glm::vec3(0.5);
      lamp.ambient = lamp.diffuse * glm::vec3(0.2f);


      glfwSwapBuffers(window);

   }


   /**
    * END TEST CODE
    */

   glfwTerminate();

   return 0;

}