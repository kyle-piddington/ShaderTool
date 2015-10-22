#include "ErrorScene.h"

ErrorScene::ErrorScene() : EmptyScene(),
errProgram(nullptr),
errTexture("assets/textures/CDTI_Display.png")
{
   
   GLfloat vertices[] = {
      1.0f, 1.0f, 0.00f, 1.0f, 0.0f,
      1.0f, -1.0f, 0.00f, 1.0f, 1.0f,
      -1.0f, -1.0f, 0.00f, 0.0f, 1.0f,
      -1.0f, 1.0f, 0.00f, 0.0f, 0.0f
   };
   unsigned int indicies[] = {
      0, 1, 3,
      1, 2, 3
   };
   
   vbo.setData(vertices, 4*5);
   ebo.setData(indicies, 6);
}

void ErrorScene::initPrograms()
{
   errProgram = createProgram("Shader Error Program");
   errProgram->addVertexShader("assets/shaders/error_vert.vs");
   errProgram->addFragmentShader("assets/shaders/tex_frag.fs");
}


void ErrorScene::initialBind()
{
   glClearColor(0.75f, 0.52f, 0.3f, 1.0f);
   glEnable(GL_DEPTH_TEST);

   errProgram->addAttribute("position");
   errProgram->addAttribute("vertTexCoords");
   errProgram->addUniform("tex");
   
   errVAO.addAttribute(errProgram->getAttribute("position"),vbo,5*sizeof(GLfloat));
   errVAO.addAttribute(errProgram->getAttribute("vertTexCoords"),vbo,5*sizeof(GLfloat),3*sizeof(GLfloat),2);
   errVAO.addElementArray(ebo);

}

void ErrorScene::render()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   errProgram->enable();
   errVAO.bind();
   errTexture.enable(errProgram->getUniform("tex").getID());
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   errVAO.unbind();
   errTexture.disable();
   errProgram->disable();
}


void ErrorScene::cleanup()
{
   
}