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

std::string ToolSceneProgramManager::getVertexName() const
{
   if(activeProgram == nullptr)
   {
      return "NULL";
   }
   return "TODO";
}
std::string ToolSceneProgramManager::getFragmentName() const
{
   if(activeProgram == nullptr)
   {
      return "NULL";
   }
   return "TODO";
}

const std::shared_ptr<Program> ToolSceneProgramManager::getActiveProgram() const
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