#include "DeferredRenderScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "GlmUtil.h"

#define NR_LIGHTS 32
DeferredRenderScene::DeferredRenderScene(Context * ctx):
CameraScene(ctx),
currentRenderType(RENDER_POSITION),
cryModel("assets/models/nanosuit/nanosuit.obj")
{
   FramebufferConfiguration cfg(ctx->getWindowWidth(),ctx->getWindowHeight());
   TextureAttachment posBfr("position",GL_RGB16F,GL_RGB,GL_FLOAT,GL_COLOR_ATTACHMENT0);
   TextureAttachment norBfr("normal",GL_RGB16F,GL_RGB,GL_FLOAT,GL_COLOR_ATTACHMENT1);
   TextureAttachment spec_albedoBfr("color",GL_RGBA,GL_RGBA,GL_FLOAT,GL_COLOR_ATTACHMENT2);
   cfg.addTexturebuffer(posBfr);
   cfg.addTexturebuffer(norBfr);
   cfg.addTexturebuffer(spec_albedoBfr);
   cfg.addRenderbuffer(RenderbufferAttachment(GL_DEPTH24_STENCIL8,GL_DEPTH_STENCIL_ATTACHMENT));
   gBuffer.init(cfg);

   deferredGBufferProg = createProgram("G_Buffer fill program");
   postProcessProg = createProgram("G_Buffer display program");
   debugProg = createProgram("Light display program");
}

void DeferredRenderScene::initPrograms()
{
   deferredGBufferProg->addVertexShader("assets/shaders/deferred/deferred_vert.vs");
   deferredGBufferProg->addFragmentShader("assets/shaders/deferred/deferred_frag.fs");

   postProcessProg->addVertexShader("assets/shaders/postprocess_vert.vs");
   postProcessProg->addFragmentShader("assets/shaders/deferred/deferred_simpleLight.fs");

   debugProg->addVertexShader("assets/shaders/debug_vert.vs");
   debugProg->addFragmentShader("assets/shaders/debug_frag.fs");  
}

void DeferredRenderScene::initialBind()
{
   deferredGBufferProg->addUniform("M");
   deferredGBufferProg->addUniform("V");
   deferredGBufferProg->addUniform("P");
   deferredGBufferProg->addUniform("N");

   deferredGBufferProg->addUniformArray("diffuseTextures",3);
   deferredGBufferProg->addUniform("numDiffuseTextures");
   deferredGBufferProg->addUniformArray("specularTextures",2);
   deferredGBufferProg->addUniform("numSpecularTextures");



   postProcessProg->addUniform("M");
   postProcessProg->addUniform("posTexture");
   postProcessProg->addUniform("norTexture");
   postProcessProg->addUniform("albedo_specTexture");
   postProcessProg->addUniform("viewPos");
   GL_Structure lightStruct;
   lightStruct.addAttribute("pos");
   lightStruct.addAttribute("color");
   lightStruct.addAttribute("Linear");
   lightStruct.addAttribute("Quadratic");
   postProcessProg->addStructArray("lights",NR_LIGHTS,lightStruct);


   debugProg->addUniform("M");
   debugProg->addUniform("V");
   debugProg->addUniform("P");
   debugProg->addUniform("debugColor");



   glClearColor(0.1,0.1,0.1,1.0);
   
   postProcessProg->enable();
   glm::mat4 I (1.0);
   glUniformMatrix4fv(postProcessProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(I));
   

   Program::UniformStructArrayInfo info = postProcessProg->getStructArray("lights");

   srand(13);
   for (GLuint i = 0; i < NR_LIGHTS; i++)
   {
        // Calculate slightly random offsets
      GLfloat xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
      GLfloat yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
      GLfloat zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
      glm::vec3 pos(xPos, yPos, zPos);
        // Also calculate random color
      GLfloat rColor = ((rand() % 100) / 200.0f) + 0.5; // Between 0.5 and 1.0
      GLfloat gColor = ((rand() % 100) / 200.0f) + 0.5; // Between 0.5 and 1.0
      GLfloat bColor = ((rand() % 100) / 200.0f) + 0.5; // Between 0.5 and 1.0
      glm::vec3 color(rColor, gColor, bColor);
      glUniform3fv(info[i]["pos"],1,glm::value_ptr(pos));
      lightPositions.push_back(pos);
      glUniform3fv(info[i]["color"],1,glm::value_ptr(color));
      lightColors.push_back(color);
      glUniform1f(info[i]["Linear"],0.7);
      glUniform1f(info[i]["Quadratic"],1.8);
   }

   postProcessProg->disable();

   deferredGBufferProg->enable();
   glm::mat4 P = camera.getPerspectiveMatrix();
   glUniformMatrix4fv(deferredGBufferProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));

   debugProg->enable();
   glUniformMatrix4fv(debugProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));
   debugProg->disable();

}

void DeferredRenderScene::render()
{
   gBuffer.bindFrameBuffer();
   glClearColor(0.0,0.0,0.0,0.0);
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   deferredGBufferProg->enable();
   glm::mat4 V = camera.getViewMatrix();

   glUniformMatrix4fv(deferredGBufferProg->getUniform("V"),1,GL_FALSE,glm::value_ptr(V));
   cryModel.transform.setScale(glm::vec3(0.25));
   for(int i = -1; i <= 1; i++)
   {
      for(int j = -1; j <= 1; j++)
      {
         cryModel.transform.setPosition(glm::vec3(3 * i,-3.0,3 * j));
         glUniformMatrix4fv(deferredGBufferProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(cryModel.transform.getMatrix()));
         glm::mat3 N = GlmUtil::createNormalMatrix(glm::mat4(1.0),cryModel.transform.getMatrix());
         glUniformMatrix3fv(deferredGBufferProg->getUniform("N"),1,GL_FALSE,glm::value_ptr(N));
         cryModel.render(*deferredGBufferProg);
      }
   }
   gBuffer.unbindFrameBuffer();

   glClearColor(1.0,1.0,1.0,1.0);
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glDisable(GL_DEPTH_TEST);
   postProcessProg->enable();
   glm::vec3 viewPos = camera.transform.getPosition();
   glUniform3fv(postProcessProg->getUniform("viewPos"),1,glm::value_ptr(viewPos));
   
   Program::UniformStructArrayInfo info = postProcessProg->getStructArray("lights");
   for(int i = 0; i < NR_LIGHTS; i++)
   {
      glm::vec3 translate = glm::vec3(sin(glfwGetTime() + i) , cos(glfwGetTime() + i), cos(i - glfwGetTime()));
      translate += lightPositions[i];
      glUniform3fv(info[i]["pos"],1,glm::value_ptr(translate));
   }
   gBuffer.enableTexture("position",postProcessProg->getUniform("posTexture"));
   gBuffer.enableTexture("normal",postProcessProg->getUniform("norTexture"));
   gBuffer.enableTexture("color",postProcessProg->getUniform("albedo_specTexture"));
   

   renderPlane.render();
   postProcessProg->disable();


   glEnable(GL_DEPTH_TEST);
   //Blit depth component of framebuffer
   glBindFramebuffer(GL_READ_FRAMEBUFFER,gBuffer.getFramebufferID());
   glBindFramebuffer(GL_DRAW_FRAMEBUFFER,0);
   glBlitFramebuffer(
      0, 0, getContext()->getWindowWidth(), getContext()->getWindowHeight(), 0, 0, getContext()->getWindowWidth(), getContext()->getWindowHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST
   );
   
   Framebuffer::BindDefaultFramebuffer();
   debugProg->enable();
   glUniformMatrix4fv(debugProg->getUniform("V"),1,GL_FALSE,glm::value_ptr(V));
   Transform cubeTransform;
   cubeTransform.setScale(glm::vec3(0.25));
   for(int i = 0; i < NR_LIGHTS; i++)
   {
      glm::vec3 translate = glm::vec3(sin(glfwGetTime() * (i%3) + i) , cos(glfwGetTime()* (i%3) + i), cos(i - glfwGetTime()));
      translate += lightPositions[i];
      cubeTransform.setPosition(translate);
      glUniformMatrix4fv(debugProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(cubeTransform.getMatrix()));
      glUniform3fv(debugProg->getUniform("debugColor"),1,glm::value_ptr(lightColors[i]));
      cube.render();

   }
   debugProg->disable();
}

void DeferredRenderScene::update()
{
   CameraScene::update();
   if(Keyboard::key(GLFW_KEY_1))
   {
      currentRenderType = RENDER_POSITION;
   }
   if(Keyboard::key(GLFW_KEY_2))
   {
      currentRenderType = RENDER_NORMAL;
   }
   if(Keyboard::key(GLFW_KEY_3))
   {
      currentRenderType = RENDER_COLOR;
   }
   if(Keyboard::key(GLFW_KEY_4))
   {
      currentRenderType = RENDER_SPECULAR;
   }
   
}

