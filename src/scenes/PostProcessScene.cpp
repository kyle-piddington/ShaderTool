#include "PostProcessScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "GL_Logger.h"

PostProcessScene::PostProcessScene(Context * ctx) :
CameraScene(ctx),
metal("assets/textures/metal.png"),
marble("assets/textures/container.jpg"),
fbo(FramebufferConfiguration::DefaultFramebuffer(ctx->getWindowWidth(),ctx->getWindowHeight()))
{
   texProg = createProgram("Diffuse texture program");
   postprocessProg = createProgram("Postprocess render program");
   plane.transform.setScale(glm::vec3(5.0f));
   plane.transform.setPosition(glm::vec3(0,-0.501,0));
   cube1.transform.setPosition(glm::vec3(-1.0f, 0.0f, -1.0f));
   cube2.transform.setPosition(glm::vec3(2.0,0.0,0.0));

}
PostProcessScene::~PostProcessScene()
{

}
void PostProcessScene::initPrograms()
{
   texProg->addVertexShader("assets/shaders/tex_vert_layout.vs");
   texProg->addFragmentShader("assets/shaders/tex_frag.fs");
   postprocessProg->addVertexShader("assets/shaders/postprocess_vert.vs");
   postprocessProg->addFragmentShader("assets/shaders/postprocess_frag_blur.fs");
}

void PostProcessScene::initialBind()
{
   texProg->addUniform("M");
   texProg->addUniform("V");
   texProg->addUniform("P");
   texProg->addUniform("tex");

   postprocessProg->addUniform("screenTexture");
   postprocessProg->addUniform("M");

   glm::mat4 P;
   texProg->enable();
   P = camera.getPerspectiveMatrix();
   texProg->getUniform("P").bind(P);
   texProg->disable();

   postprocessProg->enable();
   glm::mat4 I(1.0);
   postprocessProg->getUniform("M").bind(I);
   postprocessProg->disable();

   glClearColor(0.2,0.2,0.2,1.0);
}
void PostProcessScene::render()
{
   fbo.bindFrameBuffer();
   glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
   glEnable(GL_DEPTH_TEST);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   GL_Logger::LogError("Render setup", glGetError());
   renderGeometry();

   Framebuffer::BindDefaultFramebuffer();
   glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
   glClear(GL_COLOR_BUFFER_BIT);
   glDisable(GL_DEPTH_TEST);
   renderFrameBuffer();

}

void PostProcessScene::renderGeometry()
{
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

   metal.enable(texProg->getUniform("tex").getID());
   texProg->getUniform("M").bind(plane.transform.getMatrix());
   plane.render();
   metal.disable();
   texProg->disable();


}

void PostProcessScene::renderFrameBuffer()
{

   postprocessProg->enable();

   fbo.enableTexture("color",postprocessProg->getUniform("screenTexture").getID());
   renderPlane.render();
   postprocessProg->disable();

}
void PostProcessScene::update()
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

void PostProcessScene::cleanup()
{
   postprocessProg->enable();
   fbo.disableTexture("color");
   postprocessProg->disable();
}
