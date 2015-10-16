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
   
   visualizeNormalProgram->addVertexShader("assets/shaders/extrude_normals_vert.vs");
   visualizeNormalProgram->addGeometryShader("assets/shaders/extrude_normals.gs");
   visualizeNormalProgram->addFragmentShader("assets/shaders/debug_frag.fs");
   
   drawModelProg->addVertexShader("assets/shaders/tex_assimp_vert.vs");
   drawModelProg->addFragmentShader("assets/shaders/tex_assimp_frag.fs");
}

void VisualizeNormalScene::initialBind()
{
   glm::mat4 P = camera.getPerspectiveMatrix();
   visualizeNormalProgram->addUniform("M");
   visualizeNormalProgram->addUniform("V");
   visualizeNormalProgram->addUniform("P");

   visualizeNormalProgram->addUniform("debugColor");
   visualizeNormalProgram->enable();
   visualizeNormalProgram->getUniform("debugColor").bind(glm::vec3(1.0,0.0,1.0));
   visualizeNormalProgram->getUniform("P").bind(P);
   visualizeNormalProgram->disable();

   drawModelProg->addUniform("M");
   drawModelProg->addUniform("V");
   drawModelProg->addUniform("P");
   drawModelProg->addUniformArray("diffuseTextures",3);
   drawModelProg->addUniform("numDiffuseTextures");
   drawModelProg->enable();
   drawModelProg->getUniform("P").bind(P);
   drawModelProg->disable();
}

void VisualizeNormalScene::render()
{
   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
   renderGeometry(drawModelProg);
   renderGeometry(visualizeNormalProgram);
   //renderGeometry(visualizeNormalProgram);
}

void VisualizeNormalScene::renderGeometry(Program * prog)
{

   glm::mat4 V = camera.getViewMatrix();
   prog->enable();
   prog->getUniform("V").bind(V);
   prog->getUniform("M").bind(model.transform.getMatrix());
   model.render(*prog);
   prog->disable();


}

