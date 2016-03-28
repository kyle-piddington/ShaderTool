#include "GL_Logger.h"
#include "ToolSceneProgramManager.h"
#include "UniformObjectControllerFactory.h"
#include "DirectoryHandler.h"

ToolSceneProgramManager::ToolSceneProgramManager(std::string shaderPath):
currM(1.0),
pathName(shaderPath)
{
   assert(pathName.size() > 0);
   loadShaderNames(pathName);
   populateReservedNames();
}

bool ToolSceneProgramManager::setProgram(Program * program)
{
   this->activeProgram = std::shared_ptr<Program>(program);
   if(program->isCreated())
   {
      refreshControllers();
   }
   return true;

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

const std::vector<std::string> & ToolSceneProgramManager::getVertexShaderNames() const
{
   return vShaderNames;
}


const std::vector<std::string> & ToolSceneProgramManager::getFragmentShaderNames() const
{
   return fShaderNames;
}

void ToolSceneProgramManager::setVertexShader(std::string shader)
{
   activeProgram->addVertexShader(shader);
}
void ToolSceneProgramManager::setFragmentShader(std::string shader)
{
   activeProgram->addFragmentShader(shader);
}

bool ToolSceneProgramManager::reload()
{
   /**
    * Recreate the program
    */
   std::cout << "Refreshing!" << std::endl;

   if(!activeProgram->forceProgramRecompile())
   {
      std::cout << "Error recompiling?" << std::endl;
      return false;
   }
   else
   {
      std::cout <<  "Should have   " << exposedControlers.size()  + internalControllers.size() << " existing controllers" << std::endl;
      refreshControllers();
      updateModelMatrix(currM);
      bindDefaultVariables(currV,currP,iCurrGlobalTime);
      GL_Logger::LogError("Errors setting up managed program");
      return true;

   }
}

void ToolSceneProgramManager::updateModelMatrix(glm::mat4 M)
{

   currM = M;
   currN = glm::transpose(glm::inverse(currV*M));
   if(internalControllers.find("M") != internalControllers.end())
   {
      internalControllers["M"]->bind(currM);
   }
   if(internalControllers.find("N") != internalControllers.end())
   {
   
      internalControllers["N"]->bind(currN);
   }

}
void ToolSceneProgramManager::bindDefaultVariables(glm::mat4 V, glm::mat4 P, float iGlobalTime)
{
   currV = V;
   currP = P;
   iCurrGlobalTime = iGlobalTime;
   currN = glm::transpose(glm::inverse(currV*currM));

   if(activeProgram->hasUniform("P"))
   {
      activeProgram->getUniform("P").bind(currP);
   }
   if(activeProgram->hasUniform("V"))
   {
      activeProgram->getUniform("V").bind(currV);
   }

   if(activeProgram->hasUniform("iGlobalTime"))
   {
      activeProgram->getUniform("iGlobalTime").bind(iCurrGlobalTime);
   }
   if(internalControllers.find("N") != internalControllers.end())
   {
      internalControllers["N"]->bind(currN);
   }

}




void ToolSceneProgramManager::refreshControllers()
{
   std::vector<std::shared_ptr <UniformObjectController> > oldControllers;
   oldControllers.insert(oldControllers.end(),exposedControlers.begin(),exposedControlers.end());
   for(auto internalController : internalControllers)
   {
      oldControllers.push_back(internalController.second);
   }
   std::cout <<  "Got   " << oldControllers.size() << " old controllers" << std::endl;

   exposedControlers.clear();
   internalControllers.clear();
   activeProgram->enable();
   if(activeProgram)
   {
      std::vector <std::shared_ptr <UniformObject> > uniforms = activeProgram->getAllActiveUniforms();
      for(auto unif : uniforms)
      {
         assignController(unif,oldControllers);
      }
   }

   for(auto internalController : internalControllers)
   {
      internalController.second->refresh();
   }
   for(auto expController : exposedControlers)
   {
      expController->refresh();
   }
   std::cout <<  "Should have   " << exposedControlers.size()  + internalControllers.size() << " new controllers" << std::endl;
   activeProgram->disable();

}
void ToolSceneProgramManager::populateReservedNames()
{
   reservedNames.insert("P");
   reservedNames.insert("V");
   reservedNames.insert("M");
   reservedNames.insert("N");
   reservedNames.insert("iGlobalTime");

}

void ToolSceneProgramManager::assignController(std::shared_ptr<UniformObject> obj,  std::vector<std::shared_ptr<UniformObjectController>> & oldControllers)
{

   std::shared_ptr<UniformObjectController> ctrl = bindOldController(obj, oldControllers);
   if(ctrl == nullptr)
   {
      ctrl = UniformObjectControllerFactory::Create(obj);
   }

   if(reservedNames.find(ctrl->getName()) != reservedNames.end())
   {
      internalControllers.emplace(ctrl->getName(),ctrl);
   }
   else
   {
      exposedControlers.push_back(ctrl);
   }
}

const std::vector<std::shared_ptr<UniformObjectController>> &
   ToolSceneProgramManager::getExposedUniformControllers() const
{

   return exposedControlers;
}

std::shared_ptr<UniformObjectController> ToolSceneProgramManager::getModelUniformController()
{
   if(internalControllers.find("M") != internalControllers.end())
   {
      return internalControllers["M"];
   }
   else
   {
      return nullptr;
   }
}

std::shared_ptr<UniformObjectController> ToolSceneProgramManager::bindOldController(
      std::shared_ptr<UniformObject> obj,
      std::vector<std::shared_ptr<UniformObjectController>>  & oldControllers)
{
   std::cout <<  "Checking for  " << oldControllers.size() << "Controllers" << std::endl;
   for(auto controller : oldControllers)
   {
      std::cout <<  "Checking controller named " + controller->getName() << std::endl;

      if(controller->getName() == obj->getName() && controller->getType() == obj->getType())
      {
         std::cout <<  "rebound controller named " + controller->getName() << std::endl;
         controller->assignObject(obj);
         return controller;
      }
   }
   return nullptr;
}

std::vector<std::string> appendPath(std::string path, std::vector<std::string> rawNames)
{
   std::vector<std::string> returnVec;
   std::string pathName = path;
   if(path[pathName.size() - 1] != '/')
   {
      pathName += '/';
   }
   for (std::vector<std::string>::iterator i = rawNames.begin(); i != rawNames.end(); ++i)
   {
      returnVec.push_back(pathName + *i);
   }
   return returnVec;
}

void ToolSceneProgramManager::loadShaderNames(std::string path)
{
   if(path.size() > 0)
   {
      vShaderNames = appendPath(path,DirectoryHandler::listDirectory(path,"vs"));
      fShaderNames = appendPath(path,DirectoryHandler::listDirectory(path,"fs"));      
   }
   
}




