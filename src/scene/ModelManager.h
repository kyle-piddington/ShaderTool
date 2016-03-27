#ifndef __MODEL_MANAGER_H_
#define __MODEL_MANAGER_H_
#include "Model.h"
#include <vector>
#include <unordered_map>
class ModelManager
{
public:
   ModelManager(std::string modelPath);
   void setModel(std::shared_ptr<Model> mdl);
   void render(std::shared_ptr<Program> program);
   void load(std::string model);
   const std::vector<std::string>  & getModelNames() const;
   std::string getActiveModelName();
private:
   void loadModelNames(std::string path);
   
   std::shared_ptr<Model> mdl;
   std::vector<std::string> modelNames;
   std::unordered_map<std::string, std::shared_ptr<Model> > models;
};
#endif