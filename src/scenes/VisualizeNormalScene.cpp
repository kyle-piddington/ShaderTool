#include "VisualizeNormalsScene.h"
#include <glm/gtc/type_ptr.hpp>

VisualizeNormalScene::VisualizeNormalScene(Context * ctx):
CameraScene(ctx),
model("assets/models/nanosuit/nanosuit.obj")
{
   visualizeNormalProgram = createProgram("VisualizeNormals");
   drawModelProg = createProgram("Diffuse model draw program");
   model.transform.setScale(glm::vec3(0.1));
   model.transform.translate(glm::vec3(0,-0.5,0.0));
}
void VisualizeNormalScene::initPrograms()
{
   
   visualizeNormalProgram->addVertexShader("assets/shaders/debug_vert.vs");
   visualizeNormalProgram->addFragmentShader("assets/shaders/debug_frag.fs");
   //visualizeNormalProgram->addGeometryShader("assets/shaders/extrude_normal.gs");
   
   drawModelProg->addVertexShader("assets/shaders/tex_assimp_vert.vs");
   drawModelProg->addFragmentShader("assets/shaders/tex_assimp_frag.fs");
}

void VisualizeNormalScene::initialBind()
{
   glm::mat4 P = camera.getPerspectiveMatrix();
   visualizeNormalProgram->addUniform("M");
   visualizeNormalProgram->addUniform("V");
   visualizeNormalProgram->addUniform("P");
   visualizeNormalProgram->addUniform("NORM");

   visualizeNormalProgram->addUniform("debugColor");
   visualizeNormalProgram->enable();
   glUniform3f(visualizeNormalProgram->getUniform("debugColor"),1.0,0.0,1.0);
   glUniformMatrix4fv(visualizeNormalProgram->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));
   visualizeNormalProgram->disable();

   drawModelProg->addUniform("M");
   drawModelProg->addUniform("V");
   drawModelProg->addUniform("P");
   drawModelProg->addUniformArray("diffuseTextures",3);
   drawModelProg->addUniform("numDiffuseTextures");
   drawModelProg->enable();
   glUniformMatrix4fv(drawModelProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));
   drawModelProg->disable();
}

void VisualizeNormalScene::render()
{
   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
   renderGeometry(drawModelProg);
   //renderGeometry(visualizeNormalProgram);
}

void VisualizeNormalScene::renderGeometry(Program * prog)
{

   glm::mat4 V = camera.getViewMatrix();
   prog->enable();
   glUniformMatrix4fv(prog->getUniform("V"),1,GL_FALSE,glm::value_ptr(V));
   glUniformMatrix4fv(prog->getUniform("M"),1,GL_FALSE,glm::value_ptr(model.transform.getMatrix()));
   model.render(*prog);
   prog->disable();


}

