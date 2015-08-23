#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <easylogging++.h>
#include "VertexBuffer.h"
#include "glsl/Program.h"
#include "logger/GL_Logger.h"
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"
#include "assetWrappers/Texture2d.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Keyboard.h"
#include "GLFWHandler.h"
#include "Mouse.h"
#include "Transform.h"
#include "Material.h"
#include "TexturedMaterial.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "Spotlight.h"
INITIALIZE_EASYLOGGINGPP

#define DEG2RAD(angleDegrees) (angleDegrees * M_PI / 180.0)

const float screenWidth =800.0;
const float screenHeight = 600.0;
float pitch = 0;
float yaw = 0;
float attenuation = 50;

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
   phongProg.addVertexShader("assets/shaders/phong_vert_textured.vs");
   phongProg.addFragmentShader("assets/shaders/phong_frag_textured.fs");
   programsOK &= (phongProg.create() >= 0);

   Program lampProg("Debug Light Program");
   lampProg.addVertexShader("assets/shaders/debug_vert.vs");
   lampProg.addFragmentShader("assets/shaders/debug_frag.fs");
   programsOK &= (lampProg.create() >= 0);
   /**
    * Add program introspection to gether attribute names and uniforms later.
    */


 

   GL_Structure template_material;
 
   GL_Structure lampStruct = Light::getStruct();
   GL_Structure matStruct = Material::getStruct();
   GL_Structure dirLightStruct = DirectionalLight::getStruct();
   GL_Structure spotlightStruct = Spotlight::getStruct();
   spotlightStruct.addAttribute("mask");
   phongProg.addAttribute("position");
   phongProg.addAttribute("normal");
   phongProg.addAttribute("vertTexCoords");

   phongProg.addUniform("M");
   phongProg.addUniform("V");
   phongProg.addUniform("P");
   phongProg.addUniform("N");

   phongProg.addUniformStruct("pointLight",lampStruct);
   phongProg.addUniformStruct("material",matStruct);
   phongProg.addUniformStruct("dirLight",dirLightStruct);
   phongProg.addUniformStruct("flashLight",spotlightStruct);
  
   TexturedMaterial cubeMaterial(
      "assets/textures/container2.png",
      "assets/textures/container2_specular.png",
      "assets/textures/solid_black.png",
      32.0f);

   //Setup lights
   Light lamp(
      glm::vec3(0.2),
      glm::vec3(0.5),
      glm::vec3(1.0),
      50.0f);
   
   DirectionalLight dirLight(glm::vec3(0.2f, -1.0f, -0.3f),
                             glm::vec3(0.2),
                             glm::vec3(0.5),
                             glm::vec3(1.0));

   Spotlight spotlight(glm::vec3(0.0),
                       glm::vec3(2.9),
                       glm::vec3(2.9),
                       DEG2RAD(12.5f),
                       DEG2RAD(17.5f),
                       50.0f);
   Texture2D flashLightMask("assets/textures/awesomeface.png");

   lampProg.addAttribute("position");
   lampProg.addUniform("M");
   lampProg.addUniform("V");
   lampProg.addUniform("P");
   lampProg.addUniform("debugColor");

   GLfloat vertices[] = {
    // Positions           // Normals           // Texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
  };

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
   VertexBuffer vbo;
   ElementBufferObject ebo;
   vbo.setData(vertices,36*8);
   //ebo.setData(indices,6);
   VertexArrayObject vao;
   vao.addAttribute(phongProg.getAttribute("position"),vbo,8*sizeof(GLfloat));
   vao.addAttribute(phongProg.getAttribute("normal"),vbo,8*sizeof(GLfloat),3*sizeof(GLfloat));
   vao.addAttribute(phongProg.getAttribute("vertTexCoords"),vbo,8*sizeof(GLfloat),6*sizeof(GLfloat),2);

   VertexArrayObject lightVAO;
   lightVAO.addAttribute(phongProg.getAttribute("position"),vbo, 8*sizeof(GLfloat));

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
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

   glUniformMatrix4fv(phongProg.getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));
   GL_Logger::LogError("Could not set uniform perspective 1", glGetError());
   cubeMaterial.bind(
         matStruct.get("diffuse"),
         matStruct.get("specular"),
         matStruct.get("emission"),
         matStruct.get("shininess")

   );
   Transform cubeTransform;
   glm::vec3 cubePos(0.0f,  0.0f,  0.0f);
   glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
   cubeTransform.setPosition(cubePos);
   lamp.transform.setPosition(lightPos);
   lamp.transform.setScale(glm::vec3(0.2));

   glEnable(GL_DEPTH_TEST);
   camera.setPosition(glm::vec3(0,0,5));

   dirLight.bind(dirLightStruct.get("direction"),
                 dirLightStruct.get("ambient"),
                 dirLightStruct.get("diffuse"),
                 dirLightStruct.get("specular"));

   spotlight.transform().copy(camera.transform);
     
   while(!glfwWindowShouldClose(window) && programsOK)
   {

      glfwPollEvents();
      GLFWHandler::update();
      //Toggle Inputs
      handleCameraInput(camera);
      if(Keyboard::isKeyToggled(GLFW_KEY_O))
      {
         P = camera.getOrthographicMatrix();
      }
      else
      {
         P = camera.getPerspectiveMatrix();
      }
      //Draw loop starts
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      vao.bind();
      phongProg.enable();
      V = camera.getViewMatrix();
      glUniformMatrix4fv(phongProg.getUniform("V"), 1, GL_FALSE, glm::value_ptr(V));
      glUniformMatrix4fv(phongProg.getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));
      spotlight.transform().copy(lamp.transform);
      spotlight.transform().setRotation(glm::vec3(0,0,0));
     //spotlight.transform().lookAt(camera.transform.getPosition() + camera.transform.forward() * 3.f + glm::vec3(0.2*sin(glfwGetTime()*2.0), 0.2*cos(glfwGetTime() * 1.3),0.0));
      
      lamp.bind(
         lampStruct.get("position"),
         lampStruct.get("ambient"),
         lampStruct.get("diffuse"),
         lampStruct.get("specular"),
         lampStruct.get("constant"),
         lampStruct.get("linear"),
         lampStruct.get("quadratic"));
      flashLightMask.enable(phongProg.getUniform("flashLight.mask"));

      spotlight.bind(
        spotlightStruct.get("position"),
        spotlightStruct.get("direction"),
        spotlightStruct.get("ambient"),
        spotlightStruct.get("diffuse"),
        spotlightStruct.get("specular"),
        spotlightStruct.get("cutOff"),
        spotlightStruct.get("outerCutOff"),
        spotlightStruct.get("constant"),
        spotlightStruct.get("linear"),
        spotlightStruct.get("quadratic"));

      for(int i = 0; i < 10; i++)
      {
        cubeTransform.setPosition(cubePositions[i]);
        cubeTransform.setRotation(glm::vec3(M_PI/12 * i, M_PI/6 * i, 0.0));
        M = cubeTransform.getMatrix();
        NORM = createNormalMatrix(V, M);
        glUniformMatrix3fv(phongProg.getUniform("N"), 1, GL_FALSE, glm::value_ptr(NORM));
        glUniformMatrix4fv(phongProg.getUniform("M"), 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES,0,36);
      }


      flashLightMask.disable();





      //Draw lamp

      lampProg.enable();
      lightVAO.bind();
      M = lamp.transform.getMatrix();
      glUniformMatrix4fv(lampProg.getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));
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
      lamp.setRange(attenuation);

      if(Keyboard::isKeyDown(GLFW_KEY_M))
      {
        attenuation+=3;
      }
      if(Keyboard::isKeyDown(GLFW_KEY_N))
      {
        attenuation = fmax(0,attenuation-3);
      }


      glfwSwapBuffers(window);

   }
   //Release textures
   cubeMaterial.unbind();

   /**
    * END TEST CODE
    */

   glfwTerminate();

   return 0;

}