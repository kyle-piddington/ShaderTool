#include "AssimpScene.h"
#include "GL_Logger.h"
#include <glm/gtc/type_ptr.hpp>
void AssimpScene::handleCameraInput()
{

   const float Cam_Speed = 1.0/10.0;
   const float Cam_Rot_Speed = M_PI;
   glm::vec3 translate(0.0);
   glm::vec3 rotate(0.0);
   if(Keyboard::isKeyDown(GLFW_KEY_W))
   {
      translate += camera->transform.forward() * Cam_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_S))
   {
      translate -= camera->transform.forward() * Cam_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_A))
   {
      translate-= camera->transform.right() * Cam_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_D))
   {
      translate+= camera->transform.right() * Cam_Speed;
   }
   if(Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT))
   {

      rotate.x = (Mouse::getLastY() - Mouse::getY())/(float)(getContext()->getWindowHeight())/2.0 * Cam_Rot_Speed;
      rotate.y = (Mouse::getLastX() - Mouse::getX())/(float)(getContext()->getWindowWidth())/2.0 * Cam_Rot_Speed;
      pitch += rotate.x;
      yaw += rotate.y;
      rotate.z = 0;
   }
   camera->translate(translate);
   camera->setRotation(glm::vec3(pitch,yaw,0));
}

glm::mat3 AssimpScene::createNormalMatrix(const glm::mat4 & view, const glm::mat4 & model)
{
   return glm::mat3(glm::transpose(glm::inverse(view * model)));
}

AssimpScene::AssimpScene(Context * ctx):
   EmptyScene(),
   pitch(0),
   yaw(0),
   light1(glm::vec3(0.05),glm::vec3(1.0),glm::vec3(1.0),150),
   light2(glm::vec3(0.05),glm::vec3(0.7),glm::vec3(1.0),150)
   
   {
      camera = new Camera(ctx->getWindowWidth(), ctx->getWindowHeight());
      model = new Model("assets/models/nanosuit/nanosuit.obj");
      assimpProg = createProgram("Assimp model viewer");
      camera->setPosition(glm::vec3(0,3,5));
      light1.transform.setPosition(glm::vec3(2.3f, -1.6f, -3.0f));
      light2.transform.setPosition(glm::vec3(-1.7f, 0.9f, 1.0f));
   }
void AssimpScene::initPrograms()
{
   assimpProg->addVertexShader("assets/shaders/assimp_vert.vs");
   assimpProg->addFragmentShader("assets/shaders/assimp_frag.fs");
}

void AssimpScene::initialBind()
{
   assimpProg->addUniform("M");
   assimpProg->addUniform("V");
   assimpProg->addUniform("P");
   assimpProg->addUniform("N");


   assimpProg->addUniformArray("diffuseTextures",3);
   
   assimpProg->addStructArray("pointLights",2,Light::getStruct());
   assimpProg->addUniform("numDiffuseTextures");
   
   assimpProg->addUniformArray("specularTextures",2);
   assimpProg->addUniform("numSpecularTextures");
   
   glClearColor(0.1,0.1,0.1,1.0);

   assimpProg->enable();
   light1.bind(assimpProg->getStructArray("pointLights")[0]);
   light2.bind(assimpProg->getStructArray("pointLights")[1]);
    GL_Logger::LogError("Any errors after lighting..", glGetError());
  
   assimpProg->disable();

   
}

void AssimpScene::render()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glm::mat4 M, V, P;
   glm::mat3 NORM;
   Transform modelTransform;
   modelTransform.setScale(glm::vec3(0.2));
   modelTransform.setRotation(glm::vec3(0,glfwGetTime(),0));
   if(Keyboard::isKeyToggled(GLFW_KEY_O))
   {
      P = camera->getOrthographicMatrix();
   }
   else
   {
      P = camera->getPerspectiveMatrix();
   }
   V = camera->getViewMatrix();
   M = modelTransform.getMatrix();
   NORM = createNormalMatrix(V, M);

   GL_Logger::LogError("Any errors before enabling..", glGetError());
   assimpProg->enable();
  
   glUniformMatrix4fv(assimpProg->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));
   glUniformMatrix4fv(assimpProg->getUniform("V"), 1, GL_FALSE, glm::value_ptr(V));
   glUniformMatrix4fv(assimpProg->getUniform("M"), 1, GL_FALSE, glm::value_ptr(M));
   glUniformMatrix3fv(assimpProg->getUniform("N"), 1, GL_FALSE, glm::value_ptr(NORM));
  
   model->render(*assimpProg);

   assimpProg->disable();

}

void AssimpScene::update()
{
   handleCameraInput();
   if(Keyboard::key(GLFW_KEY_L))
   {
      if(Keyboard::isKeyToggled(GLFW_KEY_L))
      {
         glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      }
      else
      {
         glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
      }
   }
}