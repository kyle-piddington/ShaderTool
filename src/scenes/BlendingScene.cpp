#include "BlendingScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "GL_Logger.h"
BlendingScene::BlendingScene(Context * ctx) :
CameraScene(ctx),
metal("assets/textures/metal.png"),
marble("assets/textures/marble.jpg"),
grass("assets/textures/grass.png",true)
{
   alphaTexProg = createProgram("Alpha texture program");
   plane.transform.setScale(glm::vec3(5.0f));
   plane.transform.setPosition(glm::vec3(0,-0.501,0));
   cube1.transform.setPosition(glm::vec3(-1.0f, 0.0f, -1.0f));
   cube2.transform.setPosition(glm::vec3(2.0,0.0,0.0));
   grassQuad.transform.setRotation(glm::vec3(-M_PI/2.0,0,0));
   grassQuad.transform.setScale(glm::vec3(0.5));


}
BlendingScene::~BlendingScene()
{

}
void BlendingScene::initPrograms()
{
   alphaTexProg->addVertexShader("assets/shaders/tex_vert_layout.vs");
   alphaTexProg->addFragmentShader("assets/shaders/tex_frag_transparent.fs");


}

void BlendingScene::initialBind()
{
   alphaTexProg->addUniform("M");
   alphaTexProg->addUniform("V");
   alphaTexProg->addUniform("P");
   alphaTexProg->addUniform("tex");




   glm::mat4 P;
   alphaTexProg->enable();
   P = camera.getPerspectiveMatrix();
   glUniformMatrix4fv(alphaTexProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));
   alphaTexProg->disable();

   glClearColor(0.2,0.2,0.2,1.0);
}
void BlendingScene::render()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   GL_Logger::LogError("Render setup", glGetError());

   glm::mat4 M, V;
   V = camera.getViewMatrix();
   alphaTexProg->enable();
   cube1.transform.setScale(glm::vec3(1.0));
   cube2.transform.setScale(glm::vec3(1.0));

   glUniformMatrix4fv(alphaTexProg->getUniform("V"),1,GL_FALSE,glm::value_ptr(V));
   //Draw the two containers
   marble.enable(alphaTexProg->getUniform("tex"));
   glUniformMatrix4fv(alphaTexProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(cube1.transform.getMatrix()));
   cube1.render();
   glUniformMatrix4fv(alphaTexProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(cube2.transform.getMatrix()));
   cube2.render();
   marble.disable();
   //Draw the base plane
   metal.enable(alphaTexProg->getUniform("tex"));
   glUniformMatrix4fv(alphaTexProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(plane.transform.getMatrix()));
   plane.render();
   metal.disable();
   
   glm::vec3 posArray[5]{glm::vec3(-1.5f,  0.0f, -0.48f),
                         glm::vec3( 1.5f,  0.0f,  0.51f),
                         glm::vec3( 0.0f,  0.0f,  0.7f),
                         glm::vec3(-0.3f,  0.0f, -2.3f),
                         glm::vec3( 0.5f,  0.0f, -0.6f)};

   grass.enable(alphaTexProg->getUniform("tex"));
   for(int i = 0; i < 5; i++)
   {
      grassQuad.transform.setPosition(posArray[i]);
      glUniformMatrix4fv(alphaTexProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(grassQuad.transform.getMatrix()));
      grassQuad.render();
   }
   grass.disable();





}

void BlendingScene::update()
{
   CameraScene::update();
}
