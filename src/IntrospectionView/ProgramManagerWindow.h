#ifndef __PROGRAM_MANAGER_WINDOW_H__
#define __PROGRAM_MANAGER_WINDOW_H__
#include "ToolSceneProgramManager.h"
#include "ProgramManagerElement.h"
#include "TransformMatrixElement.h"
class ProgramManagerWindow
{
public:

   ProgramManagerWindow();
   ~ProgramManagerWindow();

   void setProgramManager(ToolSceneProgramManager * manager);
   void render();
   void refresh();

private:
   ToolSceneProgramManager * manager;
   std::shared_ptr<TransformMatrixElement> modelElement;
   std::vector< std::shared_ptr<ProgramManagerElement> > elements;

};
#endif