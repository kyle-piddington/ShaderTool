#ifndef __TOOL_SCENE_H__
#define __TOOL_SCENE_H__
#include <memory>
#include "TabletopCamera.h"
#include "Program.h"
#include "Scene.h"
#include "ToolSceneProgramManager.h"
#include "ModelManager.h"
#include "Grid.h"
#include "Framebuffer.h"
#include "RenderInfoController.h"
#include "ProgramManagerWindow.h"
/**
 * The Toolscene is the main activity scene
 * for the ShaderTool app. The Toolscene acts as the
 * view controller for the application, providing
 */
class ToolScene : public Scene
{
public:
   ToolScene(Context * ctx);

   virtual ~ToolScene();

   virtual void initPrograms();

   virtual void initialBind();

   virtual void render();

   virtual void update();

   virtual void cleanup();

private:

   void renderDeferred();
   void extractRenderInfo(RenderInfoController & ctrl);
   std::unique_ptr<TabletopCamera> camera;
   Program * baseRenderProgram;
   //The deferred render program exports a model's
   //positions, normals, depth, and texture coordinates to
   //a set of textures.
   Program * deferredRenderProgram;
   ToolSceneProgramManager programMgr;
   ModelManager modelMgr;
   RenderInfoController renderInfoController;
   Grid grid;

   //View
   ProgramManagerWindow managerWindow;
   Framebuffer gBuffer;






};
#endif