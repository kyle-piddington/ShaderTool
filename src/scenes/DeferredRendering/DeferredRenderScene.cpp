#include "DeferredRenderScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "GlmUtil.h"
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
}

void DeferredRenderScene::initPrograms()
{
   deferredGBufferProg->addVertexShader("assets/shaders/deferred/deferred_vert.vs");
   deferredGBufferProg->addFragmentShader("assets/shaders/deferred/deferred_frag.fs");

   postProcessProg->addVertexShader("assets/shaders/postprocess_vert.vs");
   postProcessProg->addFragmentShader("assets/shaders/deferred/deferred_debug.fs");

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
   postProcessProg->addUniform("renderType");
   glClearColor(0.1,0.1,0.1,1.0);
   
   postProcessProg->enable();
   glm::mat4 I (1.0);
   glUniformMatrix4fv(postProcessProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(I));
   postProcessProg->disable();

   deferredGBufferProg->enable();
   glm::mat4 P = camera.getPerspectiveMatrix();
   glUniformMatrix4fv(deferredGBufferProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));


}

void DeferredRenderScene::render()
{
   gBuffer.bindFrameBuffer();
   glClearColor(0.1,0.1,0.1,1.0);
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   deferredGBufferProg->enable();
   glm::mat4 V = camera.getViewMatrix();
   glUniformMatrix4fv(deferredGBufferProg->getUniform("V"),1,GL_FALSE,glm::value_ptr(V));
   cryModel.transform.setScale(glm::vec3(0.25));
   for(int i = -1; i <= 1; i++)
   {
      for(int j = -1; j <= 1; j++)
      {
         cryModel.transform.setPosition(glm::vec3(3*i,0,3*j));
         glUniformMatrix4fv(deferredGBufferProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(cryModel.transform.getMatrix()));
         glm::mat3 N = GlmUtil::createNormalMatrix(camera.getViewMatrix(),cryModel.transform.getMatrix());
         glUniformMatrix3fv(deferredGBufferProg->getUniform("N"),1,GL_FALSE,glm::value_ptr(N));
         cryModel.render(*deferredGBufferProg);
      }
   }
   gBuffer.unbindFrameBuffer();

   glClearColor(1.0,1.0,1.0,1.0);
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   postProcessProg->enable();
   gBuffer.enableTexture("position",postProcessProg->getUniform("posTexture"));
   gBuffer.enableTexture("normal",postProcessProg->getUniform("norTexture"));
   gBuffer.enableTexture("color",postProcessProg->getUniform("albedo_specTexture"));
   glUniform1i(postProcessProg->getUniform("renderType"),currentRenderType);
   renderPlane.render();
   postProcessProg->disable();

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

