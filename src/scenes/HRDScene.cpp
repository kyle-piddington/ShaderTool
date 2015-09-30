#include "HDRScene.h"
#include <glm/gtc/type_ptr.hpp>
HDRScene::HDRScene(Context * ctx):
   camera(ctx->getWindowWidth(),ctx->getWindowHeight()),
   woodTex("assets/textures/wood.png")
{
   tunnel.transform.setScale(glm::vec3(5.0f, 5.0f, 55.0f));
   tunnel.transform.translate(glm::vec3(0.0,0.0,25.0));

   hdrExposureProg = createProgram("Phong lighting program");
}

void HDRScene::initPrograms()
{
   hdrExposureProg->addVertexShader("assets/shaders/tex_vert.vs");
   hdrExposureProg->addFragmentShader("assets/shaders/tex_frag.fs");
}

void HDRScene::initialBind()
{
   hdrExposureProg->addUniform("M");
   hdrExposureProg->addUniform("V");
   hdrExposureProg->addUniform("P");
   hdrExposureProg->addUniform("tex");

   hdrExposureProg->enable();
   glm::mat4 P = camera.getPerspectiveMatrix();
   glUniformMatrix4fv(hdrExposureProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));
   woodTex.enable(hdrExposureProg->getUniform("tex"));

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
   woodTex.disable();
}