#include "BloomScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "Light.h"
#include "GlmUtil.h"
#include "Keyboard.h"
#include <unistd.h>
BloomScene::BloomScene(Context * ctx):
   camera(ctx->getWindowWidth(),ctx->getWindowHeight()),
   woodTex(TextureConfig("assets/textures/wood.png",GL_SRGB,GL_RGB,GL_UNSIGNED_BYTE), 64.0f,
           TextureConfig("assets/textures/solid_black.png")),
   numBlurs(0)
{

   tunnel.transform.setScale(glm::vec3(5.0f, 5.0f, 55.0f));
   tunnel.transform.translate(glm::vec3(0.0,0.0,25.0));

   bloomRenderProg = createProgram("Phong lighting program + bloom extraction");
   framebufferCombineProg = createProgram("HDR Postprocessing program");
   gaussBlurProg = createProgram("Gaussian Blur Program");

   FramebufferConfiguration config(ctx->getWindowWidth(),ctx->getWindowHeight());
   TextureAttachment attachment(TextureConfig("color",GL_RGB16F,GL_RGB,GL_FLOAT),GL_COLOR_ATTACHMENT0);
   config.addTexturebuffer(attachment);
   TextureAttachment attachment2(TextureConfig("bloomColor",GL_RGB16F,GL_RGB,GL_FLOAT),GL_COLOR_ATTACHMENT1);
   config.addTexturebuffer(attachment2);
   config.addRenderbuffer(RenderbufferAttachment(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT));
   extractionBuffer.init(config);

   TextureAttachment blurAttachment(TextureConfig("color",GL_RGB16F,GL_RGB,GL_FLOAT),GL_COLOR_ATTACHMENT0);
   FramebufferConfiguration blurConfig(ctx->getWindowWidth()/2.0,ctx->getWindowHeight()/2.0);
   blurConfig.addTexturebuffer(blurAttachment);
   blurConfig.addRenderbuffer(RenderbufferAttachment(GL_DEPTH24_STENCIL8,GL_DEPTH_STENCIL_ATTACHMENT));
   blurBuffer.init(blurConfig);



}

void BloomScene::initPrograms()
{
  bloomRenderProg->addVertexShader("assets/shaders/phong_vert_textured.vs");
  bloomRenderProg->addFragmentShader("assets/shaders/lighting/phong_frag_textured_pointLights_bloom.fs");

  framebufferCombineProg->addVertexShader("assets/shaders/postprocess_vert.vs");
  framebufferCombineProg->addFragmentShader("assets/shaders/postprocessing/postprocess_frag_toneMapping_bloom.fs");

  gaussBlurProg->addVertexShader("assets/shaders/postprocess_vert.vs");
  gaussBlurProg->addFragmentShader("assets/shaders/postprocessing/postprocess_twoPassBlur.fs");


}

void BloomScene::initialBind()
{
   bloomRenderProg->addUniform("M");
   bloomRenderProg->addUniform("V");
   bloomRenderProg->addUniform("P");
   bloomRenderProg->addUniform("N");
   bloomRenderProg->addUniformStruct("material", TexturedMaterial::getStruct());

   bloomRenderProg->addStructArray("pointLights",8,Light::getStruct());
   bloomRenderProg->addUniform("numPointLights");

   framebufferCombineProg->addUniform("M");
   framebufferCombineProg->addUniform("screenTexture");
   framebufferCombineProg->addUniform("bloomTexture");

   gaussBlurProg->addUniform("M");
   gaussBlurProg->addUniform("blurHorizontal");
   gaussBlurProg->addUniform("blurTexture");


   glm::mat4 I(1.0);
   framebufferCombineProg->enable();
   framebufferCombineProg->getUniform("M").bind(I);
   framebufferCombineProg->disable();
   gaussBlurProg->enable();
   gaussBlurProg->getUniform("M").bind(I);
   gaussBlurProg->disable();

   bloomRenderProg->enable();
   glm::mat4 P = camera.getPerspectiveMatrix();
   bloomRenderProg->getUniform("P").bind(P);
   woodTex.bind(bloomRenderProg->getUniformStruct("material"));


   std::vector<glm::vec3> lightPositions;
    lightPositions.push_back(glm::vec3(0.0f, 0.0f, 49.5f)); // back light
    lightPositions.push_back(glm::vec3(-1.4f, -1.9f, 9.0f));
    lightPositions.push_back(glm::vec3(0.0f, -1.8f, 4.0f));
    lightPositions.push_back(glm::vec3(0.8f, -1.7f, 6.0f));
    // - Colors
    std::vector<glm::vec3> lightColors;
    lightColors.push_back(glm::vec3(200.0f, 200.0f, 200.0f));
    lightColors.push_back(glm::vec3(0.1f, 0.0f, 0.0f));
    lightColors.push_back(glm::vec3(0.0f, 0.0f, 0.2f));
    lightColors.push_back(glm::vec3(0.0f, 0.1f, 0.0f));

    std::vector<float> lightAttenuation;
    lightAttenuation.push_back(20.0);
    lightAttenuation.push_back(150.0);
    lightAttenuation.push_back(150.0);
    lightAttenuation.push_back(150.0);

   Program::UniformStructArrayInfo arrInfo = bloomRenderProg->getStructArray("pointLights");
   for(int i = 0; i < 4; i++)
   {
      lights[i] = Light(glm::vec3(0.0), lightColors[i], glm::vec3(0.03), lightAttenuation[i]);
      lights[i].transform.setPosition(lightPositions[i]);
      lights[i].bind(arrInfo[i]);
   }
   bloomRenderProg->getUniform("numPointLights").bind(4);
   bloomRenderProg->disable();
}

void BloomScene::render()
{
   extractionBuffer.bindFrameBuffer();
   glClearColor(0.2,0.2,0.2,1.0);

   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
   //Geometry rendering
   glEnable(GL_DEPTH_TEST);
   bloomRenderProg->enable();
   glm::mat4 V = camera.getViewMatrix();
   bloomRenderProg->getUniform("V").bind(V);
   bloomRenderProg->getUniform("M").bind(tunnel.transform.getMatrix());
   glm::mat3 N = GlmUtil::createNormalMatrix(V,tunnel.transform.getMatrix());
   bloomRenderProg->getUniform("N").bind(N);

   tunnel.render();

   bloomRenderProg->disable();
   extractionBuffer.unbindFrameBuffer();


   //Perform Gaussian blur

   glViewport(0,0,getContext()->getWindowWidth()/2,getContext()->getWindowHeight()/2);
   blurBuffer.getActiveBuffer().bindFrameBuffer();
   gaussBlurProg->enable();
   glClearColor(0.0,0.0,0.0,1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glDisable(GL_DEPTH_TEST);
   extractionBuffer.enableTexture("bloomColor",gaussBlurProg->getUniform("blurTexture").getID());
   gaussBlurProg->getUniform("blurHorizontal").bind(1);
   postprocessQuad.render();
   blurBuffer.swap();
   
   bool blurHoriz = false;
   for(int i = 0; i < numBlurs; i++)
   {
      //Horizontal blur
      blurBuffer.getActiveBuffer().bindFrameBuffer();
      blurBuffer.getPassiveBuffer().enableTexture("color",gaussBlurProg->getUniform("blurTexture").getID());
      gaussBlurProg->getUniform("blurHorizontal").bind(blurHoriz);
      postprocessQuad.render();
      blurBuffer.swap();
      blurHoriz = !blurHoriz;
      blurBuffer.getActiveBuffer().bindFrameBuffer();
      blurBuffer.getPassiveBuffer().enableTexture("color",gaussBlurProg->getUniform("blurTexture").getID());
      gaussBlurProg->getUniform("blurHorizontal").bind(blurHoriz);

      postprocessQuad.render();
      blurBuffer.swap();
      
     //usleep(250.0);

   }
   std::cout << "Performing " << numBlurs << "blurs " << std::endl;
   blurBuffer.getActiveBuffer().unbindFrameBuffer();
   blurBuffer.swap();
   gaussBlurProg->disable();



    glViewport(0,0,getContext()->getWindowWidth(),getContext()->getWindowHeight());
   glClearColor(0.2,0.2,0.2,1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   framebufferCombineProg->enable();
   blurBuffer.getActiveBuffer().enableTexture("color",framebufferCombineProg->getUniform("bloomTexture").getID());
   extractionBuffer.enableTexture("color",framebufferCombineProg->getUniform("screenTexture").getID());
   postprocessQuad.render();
   framebufferCombineProg->disable();


   //Postprocess rendering
}



void BloomScene::update()
{
   camera.update(getContext());
   if(Keyboard::key(GLFW_KEY_L))
  {
      numBlurs++;
  }
  if(Keyboard::key(GLFW_KEY_K))
  {
      numBlurs--;
  }
}

void BloomScene::cleanup()
{
  woodTex.unbind();
  extractionBuffer.disableTexture("color");
  extractionBuffer.disableTexture("bloomColor");
  

}