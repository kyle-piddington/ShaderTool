#include "InstancingScene.h"

InstancingScene::InstancingScene(Context * ctx):
EmptyScene()
{
   VertexBuffer vb;
   GLfloat quadVertices[] = {
    // Positions     // Colors
    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
     0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
    -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

    -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
     0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
     0.05f,  0.05f,  0.0f, 1.0f, 1.0f
   };
   vb.setData(quadVertices,sizeof(float)*5*6);

   VertexBuffer offsetVBO;
   std::vector<glm::vec2> offsets;
   const GLfloat offset = 0.1f;
   for(int i = -10; i < 10; i+=2)
   {
      for(int j = -10; j < 10; j+=2)
      {
         glm::vec2 translation;
         translation.x = (GLfloat)i / 10.0f + offset;
         translation.y = (GLfloat)j / 10.0f + offset;

         offsets.push_back(translation);
      }
   }
   offsetVBO.setData(offsets);
   //Add position attribute
   quadVAO.addAttribute(0,vb,5*sizeof(float),0,2);
   //Add color attribute
   quadVAO.addAttribute(1,vb,5*sizeof(float),2*sizeof(float));

   quadVAO.addAttribute(2,offsetVBO,2*sizeof(float),0,2);

   //Update the offset index every one instance
   quadVAO.bind();
   glVertexAttribDivisor(2, 1);
   quadVAO.unbind();
   instanceProgram = createProgram("Instancing Program");
}

void InstancingScene::initialBind()
{
   instanceProgram->addUniform("time");
   glClearColor(0.0,0.0,0.0,1.0);
}
void InstancingScene::initPrograms()
{
   instanceProgram->addVertexShader("assets/shaders/instance/instance_test_vert.vs");
   instanceProgram->addFragmentShader("assets/shaders/instance/instance_test_frag.fs");
}

void InstancingScene::render()
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   instanceProgram->enable();
   quadVAO.bind();
   glDrawArraysInstanced(GL_TRIANGLES,0,6,100);
   quadVAO.unbind();
   instanceProgram->disable();
}
void InstancingScene::update()
{
}