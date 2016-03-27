#include "ModelManager.h"

#include "DirectoryHandler.h"
ModelManager::ModelManager(std::string path)
{
   loadModelNames(path);
}

void ModelManager::load(std::string modelName)
{
   std::shared_ptr<Model> loadedModel;
   if(models.find(modelName) != models.end())
   {
      if(models[modelName] == nullptr)
      {
         loadedModel = std::make_shared<Model>(modelName);
         models[modelName] = loadedModel;
      }
      else
      {
         loadedModel = models[modelName];
      }
      this->mdl = loadedModel;
   }
   else
   {
      LOG(ERROR) << "Could not find model at path " << modelName;
   }
}
std::string ModelManager::getActiveModelName()
{
   if(mdl != nullptr)
   {
      return mdl->getName();
   }
   else
   {
      return "(null)";
   }
}


void ModelManager::loadModelNames(std::string path)
{
   if(path.size() > 0)
   {
      std::vector<std::string> mNames = DirectoryHandler::listDirectory(path,"obj");
      std::string pathName = path;
      if(pathName[pathName.size() - 1] != '/')
      {
         pathName += '/';
      }
      for (std::vector<std::string>::iterator i = mNames.begin(); i != mNames.end(); ++i)
      {
         
         models.emplace(pathName + *i, nullptr);
         modelNames.push_back(pathName + *i);

      }
   }


}
void ModelManager::render(std::shared_ptr<Program> program)
{
   if(mdl != nullptr)
   {
      mdl->render(*program);
   }
}

const std::vector<std::string> & ModelManager::getModelNames() const
{
   return modelNames;
}
