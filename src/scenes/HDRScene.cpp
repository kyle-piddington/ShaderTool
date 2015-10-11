#include "HDRScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "Light.h"
#include "GlmUtil.h"
HDRScene::HDRScene(Context * ctx):
   camera(ctx->getWindowWidth(),ctx->getWindowHeight()),
   woodTex(TextureConfig("assets/textures/wood.png",GL_SRGB,GL_RGB,GL_UNSIGNED_BYTE), 64.0f,
           TextureConfig("assets/textures/solid_black.png"))
{

   tunnel.transform.setScale(glm::vec3(5.0f, 5.0f, 55.0f));
   tunnel.transform.translate(glm::vec3(0.0,0.0,25.0));

   hdrExposureProg = createProgram("Phong lighting program");
   hdrPostProcessProg = createProgram("HDR Postprocessing program");
   
   FramebufferConfiguration config(ctx->getWindowWidth(),ctx->getWindowHeight());
   TextureAttachment attachment(TextureConfig("color",GL_RGB16F,GL_RGB,GL_FLOAT),GL_COLOR_ATTACHMENT0);
   config.addTexturebuffer(attachment);
   config.addRenderbuffer(RenderbufferAttachment(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT));
   framebuffer.init(config);




}

void HDRScene::initPrograms()
{
   hdrExposureProg->addVertexShader("assets/shaders/phong_vert_textured.vs");
   hdrExposureProg->addFragmentShader("assets/shaders/lighting/phong_frag_textured_pointLights.fs");

   hdrPostProcessProg->addVertexShader("assets/shaders/postprocess_vert.vs");
   hdrPostProcessProg->addFragmentShader("assets/shaders/postprocess_frag_toneMapping.fs");


}

void HDRScene::initialBind()
{
   hdrExposureProg->addUniform("M");
   hdrExposureProg->addUniform("V");
   hdrExposureProg->addUniform("P");
   hdrExposureProg->addUniform("N");
   hdrExposureProg->addUniformStruct("material", TexturedMaterial::getStruct());

   hdrExposureProg->addStructArray("pointLights",8,Light::getStruct());
   hdrExposureProg->addUniform("numPointLights");

   hdrPostProcessProg->addUniform("M");
   hdrPostProcessProg->addUniform("screenTexture");

   hdrPostProcessProg->enable();
   glm::mat4 I(1.0);
   glUniformMatrix4fv(hdrPostProcessProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(I));
   hdrPostProcessProg->disable();


   hdrExposureProg->enable();
   glm::mat4 P = camera.getPerspectiveMatrix();
   glUniformMatrix4fv(hdrExposureProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));
   woodTex.bind(hdrExposureProg->getUniformStruct("material"));


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

   Program::UniformStructArrayInfo arrInfo = hdrExposureProg->getStructArray("pointLights");
   for(int i = 0; i < 4; i++)
   {
      lights[i] = Light(glm::vec3(0.0), lightColors[i], glm::vec3(0.03), lightAttenuation[i]);
      lights[i].transform.setPosition(lightPositions[i]);
      lights[i].bind(arrInfo[i]);
   }
   glUniform1i(hdrExposureProg->getUniform("numPointLights"),4);
   hdrExposureProg->disable();
}

void HDRScene::render()
{
   framebuffer.bindFrameBuffer();
   glClearColor(0.6,0.6,0.6,0.6);

   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);  
   //Geometry rendering
   glEnable(GL_DEPTH_TEST);
   hdrExposureProg->enable();
   glm::mat4 V = camera.getViewMatrix();
   glUniformMatrix4fv(hdrExposureProg->getUniform("V"),1,GL_FALSE,glm::value_ptr(V));
   glUniformMatrix4fv(hdrExposureProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(tunnel.transform.getMatrix()));
   glm::mat3 N = GlmUtil::createNormalMatrix(V,tunnel.transform.getMatrix());

   glUniformMatrix3fv(hdrExposureProg->getUniform("N"),1,GL_FALSE,glm::value_ptr(N));

   tunnel.render();

   hdrExposureProg->disable();
   framebuffer.unbindFrameBuffer();

   glClearColor(0.0,0.0,0.0,0.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glDisable(GL_DEPTH_TEST);
   hdrPostProcessProg->enable();
   framebuffer.enableTexture("color",hdrPostProcessProg->getUniform("screenTexture"));
   postprocessQuad.render();
   hdrPostProcessProg->disable();


   //Postprocess rendering
}



void HDRScene::update()
{
   camera.update(getContext());
}

void HDRScene::cleanup()
{
   woodTex.unbind();
   framebuffer.disableTexture("color");
}