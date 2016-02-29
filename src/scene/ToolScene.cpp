#include "ToolScene.h"

ToolScene::ToolScene(Context * ctx):
   Scene(ctx),
   grid(4.f,4.f,6,6)
{
   /**Create the camera*/
   camera = std::unique_ptr<TabletopCamera>( new TabletopCamera(
         ctx->getWindowWidth(),
         ctx->getWindowHeight()));


   //Set the default renderer
 }

 ToolScene::~ToolScene()
 {

 }

void ToolScene::initPrograms()
{
   Program * defaultProg = new Program("Default Render");
   defaultProg->addVertexShader("assets/shaders/debug_vert.vs");
   defaultProg->addFragmentShader("assets/shaders/debug_frag.fs");
   defaultProg->create();
   programMgr.setProgram(defaultProg);

   //Create the base grid program.
   baseRenderProgram = createProgram("Grid Renderer");
   baseRenderProgram->addVertexShader("assets/shaders/debug_vert.vs");
   baseRenderProgram->addFragmentShader("assets/shaders/debug_frag.fs");
}

void ToolScene::initialBind()
{
   baseRenderProgram->addUniform("M");
   baseRenderProgram->addUniform("V");
   baseRenderProgram->addUniform("P");
   baseRenderProgram->addUniform("debugColor");
   baseRenderProgram->enable();
   baseRenderProgram->getUniform("P").bind(camera->getPerspectiveMatrix());
   baseRenderProgram->getUniform("M").bind(glm::mat4(1.0));
   baseRenderProgram->getUniform("debugColor").bind(glm::vec3(0.7));
   glClearColor(0.2,0.2,0.2,1.0);

}
void ToolScene::render()
{

   glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
   //Render grid
   baseRenderProgram->enable();
   baseRenderProgram->getUniform("V").bind(camera->getViewMatrix());
   grid.render(*baseRenderProgram);
   baseRenderProgram->disable();

}
void ToolScene::update()
{
   camera->update(getContext());

}
void ToolScene::cleanup()
{

}

