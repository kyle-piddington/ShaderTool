#ifndef __MODEL_MANAGER_H_
#define __MODEL_MANAGER_H_
#include "Model.h"
class ModelManager
{
public:
   ModelManager();
   void setModel(std::shared_ptr<Model> mdl);
   void render(std::shared_ptr<Program> program);
   void load(std::string model);
private:
   std::shared_ptr<Model> mdl;
   std::vector<std::shared_ptr<Model> > models;

};
#endif