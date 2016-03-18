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
   return activeProgram->getVertexShaderName();
}
std::string ToolSceneProgramManager::getFragmentName() const
{
   if(activeProgram == nullptr)
   {
      return "NULL";
   }
   return activeProgram->getFragmentShaderName();
}

const std::shared_ptr<Program> ToolSceneProgramManager::getActiveProgram() const
{
   return activeProgram;
}

bool ToolSceneProgramManager::reload()
{
   /**
    * Recreate the program
    */

   if(!activeProgram->forceProgramRecompile())
   {
      return false;
   }
   else
   {
      bindDefaultVariables(currM,currV,currP,iCurrGlobalTime);
      return false;

   }
}

void ToolSceneProgramManager::bindDefaultVariables(glm::mat4 M, glm::mat4 V, glm::mat4 P, float iGlobalTime)
{
   currM = M;
   currV = V;
   currP = P;
   currN = glm::transpose(glm::inverse(V*M));
   iCurrGlobalTime = iGlobalTime;
   if(activeProgram->hasUniform("P"))
   {
      activeProgram->getUniform("P").bind(currP);
   }
   if(activeProgram->hasUniform("V"))
   {
      activeProgram->getUniform("V").bind(currV);
   }
   if(activeProgram->hasUniform("M"))
   {
      //activeProgram->getUniform("M").bind(currM);
   }
   if(activeProgram->hasUniform("N"))
   {
      activeProgram->getUniform("N").bind(currN);
   }
   if(activeProgram->hasUniform("iGlobalTime"))
   {
      activeProgram->getUniform("iGlobalTime").bind(iCurrGlobalTime);
   }
}


