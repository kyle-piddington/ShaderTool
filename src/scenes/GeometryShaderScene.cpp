#include "GeometryShaderScene.h"

GeometryShaderScene::GeometryShaderScene(Context * ctx)
{

   geomProgram = createProgram("Geometry shader program");
   GLfloat points[] = {
    -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // Bottom-left
   };  
   VertexBuffer vb;
   vb.setData(points,5*4);
   vao.addAttribute(0,vb,5*sizeof(float),0,2);
   vao.addAttribute(1,vb,5*sizeof(float),2*sizeof(float),3);


}

void GeometryShaderScene::initPrograms()
{
  geomProgram->addVertexShader("assets/shaders/simple_geom_vert.vs");
  geomProgram->addGeometryShader("assets/shaders/simple_geom.gs");
  geomProgram->addFragmentShader("assets/shaders/simple_geom_frag.fs");
}
void GeometryShaderScene::initialBind()
{
   glClearColor(0.0,0.0,0.0,1.0);
}
void GeometryShaderScene::render()
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   geomProgram->enable();
   vao.bind();
   glDrawArrays(GL_POINTS,0,4);
   vao.unbind();
   geomProgram->disable();
}
