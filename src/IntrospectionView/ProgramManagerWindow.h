#ifndef __PROGRAM_MANAGER_WINDOW_H__
#define __PROGRAM_MANAGER_WINDOW_H__
#include "ModelManager.h"
#include "ToolSceneProgramManager.h"

#include "ProgramManagerElement.h"
#include "TransformMatrixElement.h"
class ProgramManagerWindow
{
public:

   ProgramManagerWindow();
   ~ProgramManagerWindow();

   void setProgramManager(ToolSceneProgramManager * manager);
   void setModelManager(ModelManager * manager);
   void render();
   void refresh();

private:
   void renderModelManager();
   void renderProgramManager();
   ToolSceneProgramManager * manager;
   ModelManager * modelMgr;
   std::shared_ptr<TransformMatrixElement> modelElement;
   std::vector< std::shared_ptr<ProgramManagerElement> > elements;

};
#endif