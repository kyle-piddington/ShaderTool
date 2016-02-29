#ifndef __MODEL_MANAGER_H_
#define __MODEL_MANAGER_H_
#include "Model.h"
class ModelManager
{
public:
   ModelManager();
   void setModel(std::shared_ptr<Model> mdl);
   void render(std::shared_ptr<Program> program);
private:
   std::shared_ptr<Model> mdl;

};
#endif