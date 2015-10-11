#include "SSAOScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "GlmUtil.h"
#include <random> // necessary for generation of random floats (for sample kernel and noise texture)


#define NR_LIGHTS 32
SSAOScene::SSAOScene(Context * ctx):
CameraScene(ctx),
cryModel("assets/models/nanosuit/nanosuit.obj")
{
   FramebufferConfiguration cfg(ctx->getWindowWidth(),ctx->getWindowHeight());
   TextureConfig posBfrConfig("positionDepth",GL_RGBA16F,GL_RGBA,GL_FLOAT);
   posBfrConfig.setTextureFilter(GL_NEAREST);
   posBfrConfig.setWrapMode(GL_CLAMP_TO_EDGE);
   TextureAttachment posBfr(posBfrConfig,GL_COLOR_ATTACHMENT0);

   TextureConfig norBfrConfig("normal",GL_RGB16F,GL_RGB,GL_FLOAT);
   posBfrConfig.setTextureFilter(GL_NEAREST);
   TextureAttachment norBfr(norBfrConfig,GL_COLOR_ATTACHMENT1);

   TextureConfig spec_albedoConfig("color",GL_RGBA,GL_RGBA,GL_FLOAT);
   posBfrConfig.setTextureFilter(GL_NEAREST);


   TextureAttachment spec_albedoBfr(spec_albedoConfig,GL_COLOR_ATTACHMENT2);

   cfg.addTexturebuffer(posBfr);
   cfg.addTexturebuffer(norBfr);
   cfg.addTexturebuffer(spec_albedoBfr);
   cfg.addRenderbuffer(RenderbufferAttachment(GL_DEPTH24_STENCIL8,GL_DEPTH_STENCIL_ATTACHMENT));
   gBuffer.init(cfg);


   FramebufferConfiguration aoConfig(ctx->getWindowWidth(),ctx->getWindowHeight());
   TextureConfig aoTexture("occlusion",GL_RED,GL_RGB,GL_FLOAT);
   aoTexture.setTextureFilter(GL_NEAREST);
   TextureAttachment ssaoBufferAttachment(aoTexture,GL_COLOR_ATTACHMENT0);
   aoConfig.addTexturebuffer(ssaoBufferAttachment);
   ssaoBuffer.init(aoConfig);
   GL_Logger::LogError("Could not configure ssaoBuffer");

   //Blur buffer has same properties as ao buffer.
   FramebufferConfiguration blurConfiguration(ctx->getWindowWidth(),ctx->getWindowHeight());
   TextureConfig blurTexture("occlusion",GL_RED,GL_RGB,GL_FLOAT);
   blurTexture.setTextureFilter(GL_NEAREST);
   TextureAttachment blurBufferAttachment(blurTexture,GL_COLOR_ATTACHMENT0);
   blurConfiguration.addTexturebuffer(blurBufferAttachment);
   ssaoBlurBuffer.init(blurConfiguration);

   std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // random floats between 0.0 - 1.0
   std::default_random_engine generator;
   //Set up a noise texture
   std::vector<glm::vec3> ssaoNoiseVec;
   for (GLuint i = 0; i < 16; i++)
   {
       glm::vec3 noise(
           randomFloats(generator) * 2.0 - 1.0,
           randomFloats(generator) * 2.0 - 1.0,
           0.0f);
       ssaoNoiseVec.push_back(noise);
   }

   TextureConfig ssaoConfig("ssaoNoise",GL_RGB16F,GL_RGB,GL_FLOAT);
   ssaoConfig.setWrapMode(GL_REPEAT);
   ssaoConfig.setTextureFilter(GL_NEAREST);
   ssaoNoise.init(ssaoConfig,&ssaoNoiseVec[0],4,4);
   GL_Logger::LogError("Could not configure ssaoNoise");

   deferredGBufferProg = createProgram("SSAO GBuffer fill program");
   ssaoProgram = createProgram("SSAO creation program");
   postProcessProg = createProgram("Display AO map program");
   ssaoBlurProgram = createProgram("SSAO blur program");
   geomPlane.transform.setScale(glm::vec3(20.0));
   geomPlane.transform.setPosition(glm::vec3(0,-1,0));

   cryModel.transform.setScale(glm::vec3(0.5));
   cryModel.transform.setPosition(glm::vec3(0,0,3.5));
   cryModel.transform.rotate(-M_PI/2, glm::vec3(1.0,0,0));


}

void SSAOScene::initPrograms()
{
   deferredGBufferProg->addVertexShader("assets/shaders/deferred/ssao_gvert.vs");
   deferredGBufferProg->addFragmentShader("assets/shaders/deferred/ssao_gfrag.fs");

   ssaoProgram->addVertexShader("assets/shaders/postprocess_vert.vs");
   ssaoProgram->addFragmentShader("assets/shaders/deferred/ssao_frag.fs");

   ssaoBlurProgram->addVertexShader("assets/shaders/postprocess_vert.vs");
   ssaoBlurProgram->addFragmentShader("assets/shaders/deferred/ssao_blur.fs");

   postProcessProg->addVertexShader("assets/shaders/postprocess_vert.vs");
   postProcessProg->addFragmentShader("assets/shaders/deferred/ssao_displayResult.fs");
}

void SSAOScene::initialBind()
{

   glClearColor(0.0,0.0,0.0,0.0);

   deferredGBufferProg->addUniform("M");
   deferredGBufferProg->addUniform("V");
   deferredGBufferProg->addUniform("P");
   deferredGBufferProg->addUniform("N");

   ssaoProgram->addUniform("gPositionDepth");
   ssaoProgram->addUniform("gNormal");
   ssaoProgram->addUniform("noiseTexture");
   ssaoProgram->addUniformArray("samples",64);
   ssaoProgram->addUniform("P");

   ssaoBlurProgram->addUniform("ssaoInput");

   postProcessProg->addUniform("aoTexture");

   postProcessProg->disable();

   deferredGBufferProg->enable();
   glm::mat4 P = camera.getPerspectiveMatrix();
   glUniformMatrix4fv(deferredGBufferProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));

   ssaoProgram->enable();
   Program::UniformArrayInfo infos = ssaoProgram->getArray("samples");


   //Generate sample kernal
   std::vector<glm::vec3> sampleKernal = generateSampleKernal(infos.size());
   for(int i = 0; i < sampleKernal.size(); i++)
   {
      glUniform3fv(infos[i],1,glm::value_ptr(sampleKernal[i]));
   }
   GL_Logger::LogError("Could not set samples correctly");
   glUniformMatrix4fv(ssaoProgram->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));
   ssaoNoise.enable(ssaoProgram->getUniform("noiseTexture"));
   ssaoProgram->disable();
}

void SSAOScene::render()
{
   renderGeomoetry();
   renderSSAO();
   blurSSAO();
   renderSSAOMap();
}

void SSAOScene::renderGeomoetry()
{

   gBuffer.bindFrameBuffer();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   GL_Logger::LogError("Error before rendering geometry");
   deferredGBufferProg->enable();
   glm::mat4 V = camera.getViewMatrix();
   glUniformMatrix4fv(deferredGBufferProg->getUniform("V"),1,GL_FALSE,glm::value_ptr(V));
   //Render plane
   glUniformMatrix4fv(deferredGBufferProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(geomPlane.transform.getMatrix()));
   glm::mat3 N = GlmUtil::createNormalMatrix(camera.getViewMatrix(),geomPlane.transform.getMatrix());
   glUniformMatrix3fv(deferredGBufferProg->getUniform("N"),1,GL_FALSE,glm::value_ptr(N));
   geomPlane.render();
   glUniformMatrix4fv(deferredGBufferProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(cryModel.transform.getMatrix()));
   N = GlmUtil::createNormalMatrix(camera.getViewMatrix(),cryModel.transform.getMatrix());
   glUniformMatrix3fv(deferredGBufferProg->getUniform("N"),1,GL_FALSE,glm::value_ptr(N));
   cryModel.render(*deferredGBufferProg);
   deferredGBufferProg->disable();
   gBuffer.unbindFrameBuffer();
   
   GL_Logger::LogError("Error when rendering geometry");

}
void SSAOScene::renderSSAO()
{
   ssaoBuffer.bindFrameBuffer();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   ssaoProgram->enable();
   ssaoNoise.enable(ssaoProgram->getUniform("noiseTexture"));
   gBuffer.enableTexture("positionDepth",ssaoProgram->getUniform("gPositionDepth"));
   gBuffer.enableTexture("normal",ssaoProgram->getUniform("gNormal"));
   renderPlane.render();
   ssaoProgram->disable();
   ssaoBuffer.unbindFrameBuffer();
}
void SSAOScene::renderSSAOMap()
{
   postProcessProg->enable();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   ssaoBlurBuffer.enableTexture("occlusion",postProcessProg->getUniform("aoTexture"));
   renderPlane.render();
   postProcessProg->disable();

}
void SSAOScene::blurSSAO()
{
   ssaoBlurProgram->enable();
   ssaoBlurBuffer.bindFrameBuffer();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   ssaoBuffer.enableTexture("occlusion",ssaoBlurProgram->getUniform("ssaoInput"));
   renderPlane.render();
   ssaoBlurBuffer.unbindFrameBuffer();
   ssaoBlurProgram->disable();

}
std::vector<glm::vec3> SSAOScene::generateSampleKernal(int numSamples)
{
   std::vector<glm::vec3> sampleKernal; //Generate a sample within a unit sphere
   std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // random floats between 0.0 - 1.0
   std::default_random_engine generator;

   for (GLuint i = 0; i < numSamples; ++i)
   {
      glm::vec3 sample(
         randomFloats(generator) * 2.0 - 1.0,
         randomFloats(generator) * 2.0 - 1.0,
         randomFloats(generator)
      );
      sample = glm::normalize(sample);
      GLfloat scale = GLfloat(i) / numSamples;
      scale = GlmUtil::lerp(0.1f, 1.0f, scale * scale);
      sample *= scale;
      sampleKernal.push_back(sample);
   }
   return sampleKernal;
}

void SSAOScene::update()
{
   CameraScene::update();
   camera.rotate(0,M_PI/200.0);

}
void SSAOScene::cleanup()
{
   ssaoNoise.disable();
   ssaoBuffer.disableTexture("occlusion");
   gBuffer.disableTexture("positionDepth");
   gBuffer.disableTexture("normal");
}

