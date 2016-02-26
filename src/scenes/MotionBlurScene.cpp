#include "MotionBlurScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "GL_Logger.h"

MotionBlurScene::MotionBlurScene(Context * ctx) :
CameraScene(ctx),
metal("assets/textures/brickwall.jpg"),
marble("assets/textures/container.jpg")
{
   texProg = createProgram("Diffuse texture program");
   postProcessProg = createProgram("Postprocess render program");
   //Create framebuffer
   FramebufferConfiguration config(ctx->getWindowWidth(),ctx->getWindowHeight());
   TextureConfig colorConfig("color",GL_RGB,GL_RGB,GL_UNSIGNED_BYTE);
   colorConfig.setWrapMode(GL_CLAMP_TO_EDGE);
   TextureConfig depthConfig("depth",GL_DEPTH_COMPONENT,GL_DEPTH_COMPONENT,GL_FLOAT);
   depthConfig.setWrapMode(GL_CLAMP_TO_EDGE);
   
   
   config.addTexturebuffer(
      TextureAttachment(colorConfig,GL_COLOR_ATTACHMENT0));
   config.addTexturebuffer(
      TextureAttachment(
      depthConfig,
      GL_DEPTH_ATTACHMENT));
   fbo.init(config);

   plane.transform.setScale(glm::vec3(5.0f));
   plane.transform.setPosition(glm::vec3(0,-0.501,0));
   cube1.transform.setPosition(glm::vec3(-1.0f, 0.0f, -1.0f));
   cube2.transform.setPosition(glm::vec3(2.0,0.0,0.0));

}
MotionBlurScene::~MotionBlurScene()
{

}
void MotionBlurScene::initPrograms()
{
   texProg->addVertexShader("assets/shaders/tex_vert_layout.vs");
   texProg->addFragmentShader("assets/shaders/tex_frag.fs");
   postProcessProg->addVertexShader("assets/shaders/postprocess_vert.vs");
   postProcessProg->addFragmentShader("assets/shaders/postprocess_frag_motionBlur.fs");
}

void MotionBlurScene::initialBind()
{
   texProg->addUniform("M");
   texProg->addUniform("V");
   texProg->addUniform("P");
   texProg->addUniform("tex");


   postProcessProg->addUniform("screenTexture");
   postProcessProg->addUniform("depth");
   postProcessProg->addUniform("g_ViewProjectionInverseMatrix");
   postProcessProg->addUniform("g_PreviousViewProjectionMatrix");
   postProcessProg->addUniform("M");

   glm::mat4 P;
   texProg->enable();
   P = camera.getPerspectiveMatrix();
   texProg->getUniform("P").bind(P);
   texProg->disable();

   postProcessProg->enable();
   glm::mat4 I(1.0);
   postProcessProg->getUniform("M").bind(I);

   postProcessProg->disable();

   glClearColor(0.2,0.2,0.2,1.0);
}
void MotionBlurScene::render()
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

void MotionBlurScene::renderGeometry()
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

void MotionBlurScene::renderFrameBuffer()
{

   postProcessProg->enable();
   postProcessProg->getUniform("g_ViewProjectionInverseMatrix").bind(g_ViewProjectionInverseMatrix);
   postProcessProg->getUniform("g_PreviousViewProjectionMatrix").bind(g_PreviousViewProjectionMatrix);
   fbo.enableTexture("depth",postProcessProg->getUniform("depth").getID());
   fbo.enableTexture("color",postProcessProg->getUniform("screenTexture").getID());
   renderPlane.render();
   postProcessProg->disable();

}
void MotionBlurScene::update()
{
   g_PreviousViewProjectionMatrix = camera.getPerspectiveMatrix() * camera.getViewMatrix();
   CameraScene::update();
   g_ViewProjectionInverseMatrix = glm::inverse(camera.getPerspectiveMatrix() * camera.getViewMatrix());
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

void MotionBlurScene::cleanup()
{
   postProcessProg->enable();
   fbo.disableTexture("color");
   postProcessProg->disable();
}
