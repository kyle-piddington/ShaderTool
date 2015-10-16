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
   finalPassProgram = createProgram("Final Pass Program");

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

   finalPassProgram->addVertexShader("assets/shaders/postprocess_vert.vs");
   finalPassProgram->addFragmentShader("assets/shaders/deferred/deferred_simpleLight_ambient.fs");
}

void SSAOScene::initialBind()
{

   glClearColor(0.0,0.0,0.0,0.0);

   deferredGBufferProg->addUniform("M");
   deferredGBufferProg->addUniform("V");
   deferredGBufferProg->addUniform("P");
   deferredGBufferProg->addUniform("N");
   deferredGBufferProg->addUniform("numSpecularTextures");
   deferredGBufferProg->addUniformArray("specularTextures",2);
   deferredGBufferProg->addUniform("numDiffuseTextures");
   deferredGBufferProg->addUniformArray("diffuseTextures",3);

   ssaoProgram->addUniform("gPositionDepth");
   ssaoProgram->addUniform("gNormal");
   ssaoProgram->addUniform("noiseTexture");
   ssaoProgram->addUniformArray("samples",64);
   ssaoProgram->addUniform("P");

   ssaoBlurProgram->addUniform("ssaoInput");

   postProcessProg->addUniform("aoTexture");

   finalPassProgram->addUniform("posTexture");
   finalPassProgram->addUniform("norTexture");
   finalPassProgram->addUniform("albedo_specTexture");
   finalPassProgram->addUniform("ambient");
   finalPassProgram->addUniform("viewPos");
   finalPassProgram->addUniform("time");
   GL_Structure light;
   light.addAttribute("pos");
   light.addAttribute("color");
   light.addAttribute("Linear");
   light.addAttribute("Quadratic");

   finalPassProgram->addUniformStruct("light",light);

   deferredGBufferProg->enable();
   glm::mat4 P = camera.getPerspectiveMatrix();
   deferredGBufferProg->getUniform("P").bind(P);

   ssaoProgram->enable();
   Program::UniformArrayInfo infos = ssaoProgram->getArray("samples");


   //Generate sample kernal
   std::vector<glm::vec3> sampleKernal = generateSampleKernal(infos.size());
   for(int i = 0; i < sampleKernal.size(); i++)
   {
      glUniform3fv(infos[i],1,glm::value_ptr(sampleKernal[i]));
   }
   GL_Logger::LogError("Could not set samples correctly");
   ssaoProgram->getUniform("P").bind(P);
   ssaoNoise.enable(ssaoProgram->getUniform("noiseTexture").getID());
   ssaoProgram->disable();


   //Light properties
   const GLfloat linear = 0.09/3;
   const GLfloat quadratic = 0.032/3;
   glm::vec3 lightPos = glm::vec3(2.0, 4.0, -2.0);
   glm::vec3 lightColor = glm::vec3(0.5, 0.5, 0.9);
   
   finalPassProgram->enable();
   GL_Structure lightStruct = finalPassProgram->getUniformStruct("light");
   glUniform3fv(lightStruct["pos"],1,glm::value_ptr(lightPos));
   glUniform3fv(lightStruct["color"],1,glm::value_ptr(lightColor));
   glUniform1f(lightStruct["Linear"],linear);
   glUniform1f(lightStruct["Quadratic"],quadratic);
   finalPassProgram->disable();

}

void SSAOScene::render()
{
   renderGeomoetry();
   GL_Logger::LogError("Problem in Geom");

   renderSSAO();
   GL_Logger::LogError("Problem in SSAO Render");
   
   blurSSAO();
   GL_Logger::LogError("Problem in SSAO Blur");
   
   renderDeferred();
   GL_Logger::LogError("Problem in FinalPass");
   
}

void SSAOScene::renderGeomoetry()
{

   deferredGBufferProg->enable();
   gBuffer.bindFrameBuffer();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   GL_Logger::LogError("Error before rendering geometry");
   glm::mat4 V = camera.getViewMatrix();
   deferredGBufferProg->getUniform("V").bind(V);
   //Render plane
   deferredGBufferProg->getUniform("M").bind(geomPlane.transform.getMatrix());
   glm::mat3 N = GlmUtil::createNormalMatrix(camera.getViewMatrix(),geomPlane.transform.getMatrix());
   deferredGBufferProg->getUniform("N").bind(N);
   GL_Logger::LogError("Problem in Geom");

   geomPlane.render();
   deferredGBufferProg->getUniform("M").bind(cryModel.transform.getMatrix());
   N = GlmUtil::createNormalMatrix(camera.getViewMatrix(),cryModel.transform.getMatrix());
   deferredGBufferProg->getUniform("N").bind(N);
   GL_Logger::LogError("Problem in Geom");

   cryModel.render(*deferredGBufferProg);
   deferredGBufferProg->disable();
   gBuffer.unbindFrameBuffer();
   glDisable(GL_DEPTH_TEST);
 
   GL_Logger::LogError("Error when rendering geometry");

}
void SSAOScene::renderSSAO()
{
   ssaoBuffer.bindFrameBuffer();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   ssaoProgram->enable();
   ssaoNoise.enable(ssaoProgram->getUniform("noiseTexture").getID());
   gBuffer.enableTexture("positionDepth",ssaoProgram->getUniform("gPositionDepth").getID());
   gBuffer.enableTexture("normal",ssaoProgram->getUniform("gNormal").getID());
   renderPlane.render();
   ssaoProgram->disable();
   ssaoBuffer.unbindFrameBuffer();
}
void SSAOScene::renderSSAOMap()
{
   postProcessProg->enable();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   ssaoBlurBuffer.enableTexture("occlusion",postProcessProg->getUniform("aoTexture").getID());
   renderPlane.render();
   postProcessProg->disable();

}
void SSAOScene::blurSSAO()
{
   ssaoBlurProgram->enable();
   ssaoBlurBuffer.bindFrameBuffer();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   ssaoBuffer.enableTexture("occlusion",ssaoBlurProgram->getUniform("ssaoInput").getID());
   renderPlane.render();
   ssaoBlurBuffer.unbindFrameBuffer();
   ssaoBlurProgram->disable();

}

void SSAOScene::renderDeferred()
{
   finalPassProgram->enable();
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   gBuffer.enableTexture("positionDepth",finalPassProgram->getUniform("posTexture").getID());
   gBuffer.enableTexture("normal",finalPassProgram->getUniform("norTexture").getID());
   gBuffer.enableTexture("color",finalPassProgram->getUniform("albedo_specTexture").getID());
   ssaoBlurBuffer.enableTexture("occlusion",finalPassProgram->getUniform("ambient").getID());
   glm::vec3 viewPos = camera.transform.getPosition();
   finalPassProgram->getUniform("viewPos").bind(viewPos);
   finalPassProgram->getUniform("time").bind((float)glfwGetTime());
   renderPlane.render();
   finalPassProgram->disable();
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
   //camera.rotate(0,M_PI/200.0);

}
void SSAOScene::cleanup()
{
   ssaoNoise.disable();
   ssaoBuffer.disableTexture("occlusion");
   gBuffer.disableTexture("positionDepth");
   gBuffer.disableTexture("normal");
}

