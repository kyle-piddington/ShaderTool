#include "ShadowScene.h"
#include <glm/gtc/type_ptr.hpp>
ShadowScene::ShadowScene(Context * ctx) :
   CameraScene(ctx),
   pointLight(glm::vec3(0.1),glm::vec3(0.7),glm::vec3(0.8),50.0f)
   {
      pointLight.transform.setPosition(glm::vec3(-2.0f, 4.0f, -1.0f));
      pointLight.transform.lookAt(glm::vec3(0.0),glm::vec3(1.0));
      FramebufferConfiguration config(1024,1024);
      config.addTexturebuffer(TextureAttachment("depth",GL_DEPTH_COMPONENT,GL_FLOAT,GL_DEPTH_ATTACHMENT));
      depthBuffer.init(config);
      depthBuffer.bindFrameBuffer();
      glDrawBuffer(GL_NONE);
      glReadBuffer(GL_NONE);
      depthBuffer.unbindFrameBuffer();
      

      renderCube[0].transform.setPosition(glm::vec3(0.0f, 1.5f, 0.0));
      renderCube[1].transform.setPosition(glm::vec3(2.0f, 0.0f, 1.0));
      renderCube[2].transform.setPosition(glm::vec3(-1.0f, 0.0f, 2.0));
      renderCube[2].transform.rotate(2*M_PI/3.0, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
      renderCube[2].transform.setScale(glm::vec3(0.5));


      geomPlane.transform.setScale(glm::vec3(25.0f));
      geomPlane.transform.setPosition(glm::vec3(0,-0.5,0));
      depthPassProg = createProgram("Depth pass program");
      postprocessProg = createProgram("Depth display program");
   }



void ShadowScene::initPrograms()
{
   depthPassProg->addVertexShader("assets/shaders/depthpass_vert.vs");
   depthPassProg->addFragmentShader("assets/shaders/depthpass_frag.fs");

   postprocessProg->addVertexShader("assets/shaders/postprocess_vert.vs");
   postprocessProg->addFragmentShader("assets/shaders/postprocess_frag_displayDepth.fs");
}
void ShadowScene::initialBind()
{
   depthPassProg->addUniform("VPMatrix");
   depthPassProg->addUniform("model");

   postprocessProg->addUniform("screenTexture");

   glClearColor(0.2,0.2,0.2,1.0);

}

void ShadowScene::render()
{
   renderDepthPass();
   renderDepthMap();
}

void ShadowScene::renderDepthPass()
{
   depthBuffer.bindFrameBuffer();
   glClear(GL_DEPTH_BUFFER_BIT);
   glViewport(0, 0, depthBuffer.getWidth(), depthBuffer.getHeight());
   depthPassProg->enable();
   GLfloat near_plane = 1.0f, far_plane = 7.5f;
   glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
   glm::mat4 VPMatrix = lightProjection * glm::inverse(pointLight.transform.getMatrix());
   glUniformMatrix4fv(depthPassProg->getUniform("VPMatrix"),1,GL_FALSE,glm::value_ptr(VPMatrix));
   renderGeometry(depthPassProg->getUniform("model"));
   depthBuffer.unbindFrameBuffer();
}
void ShadowScene::renderGeometry(GLint modelMtx)
{
   for(int i = 0; i < 3; i++)
   {
      glUniformMatrix4fv(modelMtx,1,GL_FALSE,glm::value_ptr(renderCube[i].transform.getMatrix()));
      renderCube[i].render();
   }
   glUniformMatrix4fv(modelMtx,1,GL_FALSE,glm::value_ptr(geomPlane.transform.getMatrix()));
   geomPlane.render();
}

void ShadowScene::renderDepthMap()
{
   glViewport(0, 0, getContext()->getWindowWidth(), getContext()->getWindowHeight());
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   postprocessProg->enable();
   depthBuffer.enableTexture("depth",postprocessProg->getUniform("screenTexture"));
   postprocessPlane.render();
   depthBuffer.disableTexture("depth");
   postprocessProg->disable();
}
void ShadowScene::cleanup()
{
   
}
