#include "AssimpScene.h"
#include "GL_Logger.h"
#include <glm/gtc/type_ptr.hpp>

glm::mat3 AssimpScene::createNormalMatrix(const glm::mat4 & view, const glm::mat4 & model)
{
   return glm::mat3(glm::transpose(glm::inverse(view * model)));
}

AssimpScene::AssimpScene(Context * ctx):
   CameraScene(ctx),
   light1(glm::vec3(0.05),glm::vec3(1.0),glm::vec3(1.0),50),
   light2(glm::vec3(0.05),glm::vec3(1.0),glm::vec3(1.0),50),
   mat(glm::vec3(0.0),glm::vec3(0.0),glm::vec3(0.0),0),
   plane(3,3)

   {
      model = new Model("assets/models/nanosuit/nanosuit.obj");
      assimpProg = createProgram("Assimp model viewer");
      camera.setPosition(glm::vec3(0,0,2));
      light1.transform.setPosition(glm::vec3(2.3f, -1.6f, -3.0f));
      light2.transform.setPosition(glm::vec3(-1.7f, 0.9f, 1.0f));
   }

AssimpScene::~AssimpScene()
{
   delete model;
}
void AssimpScene::initPrograms()
{
   assimpProg->addVertexShader("assets/shaders/assimp_vert.vs");
   assimpProg->addFragmentShader("assets/shaders/assimp_frag.fs");
}

void AssimpScene::initialBind()
{
   assimpProg->addUniform("MV");
   assimpProg->addUniform("P");
   assimpProg->addUniform("N");


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

   //glEnable(GL_CULL_FACE);
   //glCullFace(GL_BACK);



}

void AssimpScene::render()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glm::mat4 M, V, P, MV;
   glm::mat3 NORM;
   model->transform.setPosition(glm::vec3(0.0f, -1.75f, 0.0f));
   model->transform.setScale(glm::vec3(0.2));
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
   NORM = createNormalMatrix(V, M);
   MV = V*M;
   GL_Logger::LogError("Any errors before enabling..", glGetError());
   assimpProg->enable();
   glUniformMatrix4fv(assimpProg->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));
   glUniformMatrix4fv(assimpProg->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV));
   glUniformMatrix3fv(assimpProg->getUniform("N"), 1, GL_FALSE, glm::value_ptr(NORM));
   mat.bind(assimpProg->getUniformStruct("material"));
   //model->render(*assimpProg);

   M = plane.transform.getMatrix();
   MV = V*M;
   glUniformMatrix4fv(assimpProg->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV));

   //cube.render();
   plane.render();
   assimpProg->disable();

}

void AssimpScene::update()
{
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