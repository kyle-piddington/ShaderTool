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
      model = new Model("assets/models/guard/boblampclean.md5mesh");
      assimpProg = createProgram("Assimp model viewer");
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
   
   assimpProg->addVertexShader("assets/shaders/assimp_vert.vs");
   assimpProg->addFragmentShader("assets/shaders/assimp_frag.fs");
}

void AnimScene::initialBind()
{
   assimpProg->addUniform("MV");
   assimpProg->addUniform("P");
   assimpProg->addUniform("N");

   debugProg->addUniform("M");
   debugProg->addUniform("V");
   debugProg->addUniform("P");



   assimpProg->addUniformArray("diffuseTextures",3);

   assimpProg->addStructArray("pointLights",2,Light::getStruct());
   assimpProg->addUniform("numDiffuseTextures");

   assimpProg->addUniformArray("specularTextures",2);
   assimpProg->addUniform("numSpecularTextures");

   assimpProg->addUniformStruct("material",Material::getStruct());

   glClearColor(0.1,0.1,0.1,1.0);

   assimpProg->enable();
   light1.bind(assimpProg->getStructArray("pointLights")[0]);
   light2.bind(assimpProg->getStructArray("pointLights")[1]);
    GL_Logger::LogError("Any errors after lighting..", glGetError());
   assimpProg->disable();

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
   assimpProg->enable();
   assimpProg->getUniform("P").bind(P);
   assimpProg->getUniform("MV").bind(MV);
   assimpProg->getUniform("N").bind(NORM);
   mat.bind(assimpProg->getUniformStruct("material"));
   model->render(*assimpProg);

   M = plane.transform.getMatrix();
   MV = V*M;
   assimpProg->getUniform("MV").bind(MV);
   


   //cube.render();
   plane.render();
   assimpProg->disable();
   glDisable(GL_DEPTH_TEST);
   debugProg->enable();
   debugProg->getUniform("V").bind(V);
   debugProg->getUniform("M").bind(model->transform.getMatrix());
   model->renderSkeleton();
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