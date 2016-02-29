#ifndef __TOOL_SCENE_H__
#define __TOOL_SCENE_H__
#include <memory>
#include "TabletopCamera.h"
#include "Program.h"
#include "Scene.h"
#include "ToolSceneProgramManager.h"
#include "ModelManager.h"
#include "Grid.h"
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
   std::unique_ptr<TabletopCamera> camera;
   Program * baseRenderProgram;
   ToolSceneProgramManager programMgr;
   ModelManager modelMgr;
   Grid grid;






};
#endif