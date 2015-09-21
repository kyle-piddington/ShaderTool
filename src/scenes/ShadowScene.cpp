#include "ShadowScene.h"

ShadowScene::ShadowScene(Context * ctx) :
   CameraScene(ctx),
   depthBuffer(nullptr),
   pointLight(glm::vec3(0.1),glm::vec3(0.7),glm::vec3(0.8),50.0f)
   {
      pointLight.transform.setPosition(glm::vec3(-2.0f, 4.0f, -1.0f));
      pointLight.transform.lookAt(glm::vec3(0.0));
      FramebufferConfiguration config(1024,1024);
      config.addTexturebuffer(TextureAttachment("depth",GL_DEPTH_COMPONENT,GL_FLOAT,GL_DEPTH_ATTACHMENT));

      depthBuffer = std::unique_ptr<Framebuffer>(new Framebuffer(config));

   }


void ShadowScene::initPrograms()
{

}
void ShadowScene::initialBind()
{

}
void ShadowScene::render()
{

}
void ShadowScene::cleanup()
{
   
}
