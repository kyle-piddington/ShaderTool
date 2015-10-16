#include "OutlineScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "GL_Logger.h"
OutlineScene::OutlineScene(Context * ctx) :
CameraScene(ctx),
metal("assets/textures/metal.png"),
marble("assets/textures/marble.jpg")
{
   texProg = createProgram("Diffuse texture program");
   outlineTextureProgram = createProgram("Outline texture program");
   plane.transform.setScale(glm::vec3(5.0f));
   plane.transform.setPosition(glm::vec3(0,-0.501,0));
   cube1.transform.setPosition(glm::vec3(-1.0f, 0.0f, -1.0f));
   cube2.transform.setPosition(glm::vec3(2.0,0.0,0.0));

}
OutlineScene::~OutlineScene()
{

}
void OutlineScene::initPrograms()
{
   texProg->addVertexShader("assets/shaders/tex_vert_layout.vs");
   texProg->addFragmentShader("assets/shaders/tex_frag.fs");

   outlineTextureProgram->addVertexShader("assets/shaders/debug_vert.vs");
   outlineTextureProgram->addFragmentShader("assets/shaders/debug_frag.fs");

}

void OutlineScene::initialBind()
{
   texProg->addUniform("M");
   texProg->addUniform("V");
   texProg->addUniform("P");
   texProg->addUniform("tex");

   outlineTextureProgram->addUniform("M");
   outlineTextureProgram->addUniform("V");
   outlineTextureProgram->addUniform("P");
   outlineTextureProgram->addUniform("debugColor");


   glm::mat4 P;
   texProg->enable();
   P = camera.getPerspectiveMatrix();
   texProg->getUniform("P").bind(P);
   texProg->disable();

   outlineTextureProgram->enable();
   outlineTextureProgram->getUniform("debugColor").bind(glm::vec3(0.04, 0.28, 0.26));
   outlineTextureProgram->getUniform("P").bind(P);
   outlineTextureProgram->disable();
   glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  
   glEnable(GL_STENCIL_TEST);
   glClearColor(0.2,0.2,0.2,1.0);
}
void OutlineScene::render()
{
   glEnable(GL_DEPTH_TEST);
   glStencilMask(0xFF); // Enable writing to the stencil buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glStencilFunc(GL_ALWAYS, 1, 0xFF);
  
   GL_Logger::LogError("Render setup", glGetError());

   glm::mat4 M, V;
   V = camera.getViewMatrix();
   texProg->enable();
   cube1.transform.setScale(glm::vec3(1.0));
   cube2.transform.setScale(glm::vec3(1.0));

   texProg->getUniform("V").bind(V);
   //Draw the two containers
   marble.enable(texProg->getUniform("tex").getID());
   texProg->getUniform("M").bind(cube1.transform.getMatrix());
   cube1.render();
   texProg->getUniform("M").bind(cube2.transform.getMatrix());
   cube2.render();
   marble.disable();

   glStencilMask(0x00); // Disable writing to the stencil buffer
   metal.enable(texProg->getUniform("tex").getID());
   texProg->getUniform("M").bind(plane.transform.getMatrix());
   plane.render();
   metal.disable();
   texProg->disable();

   glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
   glDisable(GL_DEPTH_TEST);
   GL_Logger::LogError("second program setup", glGetError());

   outlineTextureProgram->enable();
   outlineTextureProgram->getUniform("V").bind(V);
   cube1.transform.setScale(glm::vec3(1.1));
   cube2.transform.setScale(glm::vec3(1.1));
   outlineTextureProgram->getUniform("M").bind(cube1.transform.getMatrix());
   cube1.render();
   outlineTextureProgram->getUniform("M").bind(cube2.transform.getMatrix());
   cube2.render();
   outlineTextureProgram->disable();



}

void OutlineScene::update()
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
