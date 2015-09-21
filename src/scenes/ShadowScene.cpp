#include "ShadowScene.h"

ShadowScene::ShadowScene(Context * ctx) :
   CameraScene(ctx),
   depthBuffer(nullptr),
   pointLight(glm::vec3(0.1),glm::vec3(0.7),glm::vec3(0.8),50.0f)
   {
      pointLight.transform.setPosition(glm::vec3(-2.0f, 4.0f, -1.0f));
      pointLight.lookAt(glm::vec3(0.0));
      FramebufferConfiguration config(1024,1024);
      config.outputComponentType = GL_DEPTH_COMPONENT;
      config.outputComponentStorage = GL_FLOAT;
      depthBuffer = std::unique_ptr<Framebuffer>(new Framebuffer(config));

   }
