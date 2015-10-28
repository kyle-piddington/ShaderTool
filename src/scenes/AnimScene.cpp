#include "AnimScene.h"
#include "GL_Logger.h"
#include <glm/gtc/type_ptr.hpp>
#include "GlmUtil.h"

AnimScene::AnimScene(Context * ctx):
   CameraScene(ctx),
   light1(glm::vec3(0.05),glm::vec3(1.0),glm::vec3(1.0),50),
   light2(glm::vec3(0.05),glm::vec3(1.0),glm::vec3(1.0),50),
   mat(glm::vec3(0.0),glm::vec3(0.0),glm::vec3(0.0),0),
   plane(3,3)

   {
      model = new Model("assets/models/movecube/movecube.dae");
      animProg = createProgram("Animation viewer");
      debugProg = createProgram("Debug program");
      camera.setPosition(glm::vec3(0,0,2));
      light1.transform.setPosition(glm::vec3(2.3f, -1.6f, -3.0f));
      light2.transform.setPosition(glm::vec3(-1.7f, 0.9f, 1.0f));
      model->transform.setScale(glm::vec3(0.03));
      model->transform.setRotation(glm::vec3(-M_PI/2,0,0));

   
   
   }

AnimScene::~AnimScene()
{
   delete model;
}
void AnimScene::initPrograms()
{
   debugProg->addVertexShader("assets/shaders/debug_vert.vs");
   debugProg->addFragmentShader("assets/shaders/debug_frag.fs");
   
   animProg->addVertexShader("assets/shaders/skeleton/skel_vert.vs");
   animProg->addFragmentShader("assets/shaders/assimp_frag.fs");
}

void AnimScene::initialBind()
{
   animProg->addUniform("M");
   animProg->addUniform("V");
   animProg->addUniform("P");
   animProg->addUniformArray("gBones",100);
   animProg->addUniformArray("gBinds",100);
   debugProg->addUniform("M");
   debugProg->addUniform("V");
   debugProg->addUniform("P");



   animProg->addUniformArray("diffuseTextures",3);

   animProg->addStructArray("pointLights",2,Light::getStruct());
   animProg->addUniform("numDiffuseTextures");

   animProg->addUniformArray("specularTextures",2);
   animProg->addUniform("numSpecularTextures");

   animProg->addUniformStruct("material",Material::getStruct());

   glClearColor(0.1,0.1,0.1,1.0);

   animProg->enable();
   light1.bind(animProg->getStructArray("pointLights")[0]);
   light2.bind(animProg->getStructArray("pointLights")[1]);
    GL_Logger::LogError("Any errors after lighting..", glGetError());
   animProg->disable();

   debugProg->enable();
   debugProg->getUniform("P").bind(camera.getPerspectiveMatrix());
   debugProg->disable();

   //glEnable(GL_CULL_FACE);
   //glCullFace(GL_BACK);



}

void AnimScene::render()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   
   glm::mat4 M, V, P, MV;
   glm::mat3 NORM;
   if(Keyboard::isKeyToggled(GLFW_KEY_O))
   {
      P = camera.getOrthographicMatrix();
   }
   else
   {
      P = camera.getPerspectiveMatrix();
   }
   V = camera.getViewMatrix();
   M = model->transform.getMatrix();
   NORM = GlmUtil::createNormalMatrix(V, M);
   MV = V*M;
   GL_Logger::LogError("Any errors before enabling..", glGetError());
   animProg->enable();
   animProg->getUniform("P").bind(P);
   animProg->getUniform("M").bind(M);
   animProg->getUniform("V").bind(V);
   mat.bind(animProg->getUniformStruct("material"));
   model->render(*animProg);

   M = plane.transform.getMatrix();
   animProg->getUniform("M").bind(M);
   


   //cube.render();
   plane.render();
   animProg->disable();
   glDisable(GL_DEPTH_TEST);
   debugProg->enable();
   debugProg->getUniform("V").bind(V);
   debugProg->getUniform("M").bind(model->transform.getMatrix());
   //model->renderSkeleton();
   debugProg->disable();

}

void AnimScene::update()
{
   model->animate("imported_0",glfwGetTime());
   CameraScene::update();
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