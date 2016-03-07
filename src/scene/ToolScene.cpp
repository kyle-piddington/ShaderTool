#include "ToolScene.h"

ToolScene::ToolScene(Context * ctx):
   Scene(ctx),
   grid(4.f,4.f,6,6)

{
   /**Create the camera*/
   camera = std::unique_ptr<TabletopCamera>( new TabletopCamera(
         ctx->getWindowWidth(),
         ctx->getWindowHeight()));
   modelMgr.load("assets/models/suzanne.obj");
   glEnable(GL_CULL_FACE);
   glEnable(GL_DEPTH_TEST);
   glCullFace(GL_BACK);
   //Set the default renderer
 }

 ToolScene::~ToolScene()
 {

 }

void ToolScene::initPrograms()
{
   Program * defaultProg = new Program("Default Render");
   defaultProg->addVertexShader("assets/shaders/phong_vert.vs");
   defaultProg->addFragmentShader("assets/shaders/phong_frag.fs");
   defaultProg->create();
   programMgr.setProgram(defaultProg);
   //Create the base grid program.
   baseRenderProgram = createProgram("Grid Renderer");
   baseRenderProgram->addVertexShader("assets/shaders/debug_vert.vs");
   baseRenderProgram->addFragmentShader("assets/shaders/debug_frag.fs");

   managerWindow.setProgramManager(&(this->programMgr));

}

void ToolScene::initialBind()
{
   baseRenderProgram->enable();
   GL_Logger::LogError("Enable");
   baseRenderProgram->getUniform("P").bind(camera->getPerspectiveMatrix());
   GL_Logger::LogError("Bind P");

   baseRenderProgram->getUniform("M").bind(glm::mat4(1.0));
   GL_Logger::LogError("Bind M");
  
   baseRenderProgram->getUniform("debugColor").bind(glm::vec3(0.7));
    GL_Logger::LogError("Bind color");
   
   managerWindow.refresh();
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

   std::shared_ptr<Program> prog = programMgr.getActiveProgram();
   //If MVP, bind.
   prog->enable();
   if(prog->hasUniform("P"))
   {
      prog->getUniform("P").bind(camera->getPerspectiveMatrix());
   }
   if(prog->hasUniform("V"))
   {
      prog->getUniform("V").bind(camera->getViewMatrix());
   }
   if(prog->hasUniform("M"))
   {
      prog->getUniform("M").bind(glm::mat4(1.0));
   }
   if(prog->hasUniform("N"))
   {
      prog->getUniform("N").bind(glm::transpose(glm::inverse(camera->getViewMatrix())));
   }
   if(prog->hasUniform("iGlobalTime"))
   {
      prog->getUniform("iGlobalTime").bind(glfwGetTime());
   }
   modelMgr.render(prog);
   managerWindow.render();
   prog->disable();

}
void ToolScene::update()
{
   camera->update(getContext());

}
void ToolScene::cleanup()
{

}

