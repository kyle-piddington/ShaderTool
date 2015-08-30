#include "ErrorScene.h"

ErrorScene::ErrorScene() : EmptyScene(),
errProgram(nullptr),
errTexture("assets/textures/awesomeface.png")
{
   
   GLfloat vertices[] = {
      1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
      -1.0f, 1.0f, 0.0f, 0.0f, 1.0f
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
   errProgram->addVertexShader("error_vert.vs");
   errProgram->addFragmentShader("tex_frag.fs");
}


void ErrorScene::initialBind()
{
   errVAO.addAttribute(errProgram->getAttribute("position"),vbo,5*sizeof(GLfloat));
   errVAO.addAttribute(errProgram->getAttribute("vertTexCoords"),vbo,5*sizeof(GLfloat),3*sizeof(GLfloat),2);
   errVAO.addElementArray(ebo);
   errTexture.enable(errProgram->getUniform("tex"));
}

void ErrorScene::render()
{
   errVAO.bind();
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   errVAO.unbind();
}


void ErrorScene::cleanup()
{
   errTexture.disable();
}