#include "ToolSceneProgramManager.h"

ToolSceneProgramManager::ToolSceneProgramManager()
{

}

bool ToolSceneProgramManager::setProgram(Program * program)
{
   if(program->isCreated())
   {
      this->activeProgram = std::shared_ptr<Program>(program);
      return true;
   }
   return false;
}

std::string ToolSceneProgramManager::getVertexName()
{
   if(activeProgram == nullptr)
   {
      return "NULL";
   }
   return "TODO";
}
std::string ToolSceneProgramManager::getFragmentName()
{
   if(activeProgram == nullptr)
   {
      return "NULL";
   }
   return "TODO";
}

const std::shared_ptr<Program> ToolSceneProgramManager::getActiveProgram()
{
   return activeProgram;
}

bool ToolSceneProgramManager::reload()
{
   if(activeProgram->shouldProgramRecompile())
   {
      if(activeProgram->create())
      {
         return false;
      }
      return true;
   }
   return true;

}