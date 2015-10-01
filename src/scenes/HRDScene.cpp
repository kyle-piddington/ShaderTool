#include "HDRScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "Light.h"
HDRScene::HDRScene(Context * ctx):
   camera(ctx->getWindowWidth(),ctx->getWindowHeight()),
   woodTex("assets/textures/wood.png", 1.0f)
{
   tunnel.transform.setScale(glm::vec3(5.0f, 5.0f, 55.0f));
   tunnel.transform.translate(glm::vec3(0.0,0.0,25.0));

   hdrExposureProg = createProgram("Phong lighting program");
}

void HDRScene::initPrograms()
{
   hdrExposureProg->addVertexShader("assets/shaders/phong_vert_textured.vs");
   hdrExposureProg->addFragmentShader("assets/shaders/lighting/phong_frag_textured_pointLights.fs");
}

void HDRScene::initialBind()
{
   hdrExposureProg->addUniform("M");
   hdrExposureProg->addUniform("V");
   hdrExposureProg->addUniform("P");
   hdrExposureProg->addUniformStruct("material", TexturedMaterial::getStruct());

   hdrExposureProg->addStructArray("pointLights",8,Light::getStruct());
   hdrExposureProg->addUniform("numPointLights");
   hdrExposureProg->enable();
   glm::mat4 P = camera.getPerspectiveMatrix();
   glUniformMatrix4fv(hdrExposureProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));
   woodTex.bind(hdrExposureProg->getUniformStruct("texture"));


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

   Program::UniformStructArrayInfo arrInfo = hdrExposureProg->getStructArray("pointLights");
   for(int i = 0; i < 4; i++)
   {
      lights[i] = Light(lightColors[i]*(1.0f/20.0f), lightColors[i], glm::vec3(0.8),50.0);
      lights[i].transform.setPosition(lightColors[i]);
      lights[i].bind(arrInfo[i]);
   }
   hdrExposureProg->disable();
}

void HDRScene::render()
{
   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
   hdrExposureProg->enable();
   glm::mat4 V = camera.getViewMatrix();
   glUniformMatrix4fv(hdrExposureProg->getUniform("V"),1,GL_FALSE,glm::value_ptr(V));
   glUniformMatrix4fv(hdrExposureProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(tunnel.transform.getMatrix()));
   tunnel.render();
   hdrExposureProg->disable();
}



void HDRScene::update()
{
   camera.update(getContext());
}

void HDRScene::cleanup()
{
   woodTex.unbind();
}