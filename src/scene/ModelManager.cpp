#include "ModelManager.h"

ModelManager::ModelManager()
{

}

void ModelManager::load(std::string modelName)
{
   models.push_back(std::shared_ptr<Model> (new Model(modelName)));
   this->mdl = models.back();
}
void ModelManager::setModel(std::shared_ptr<Model> mdl)
{
   this->mdl = mdl;
}

void ModelManager::render(std::shared_ptr<Program> program)
{
   mdl->render(*program);
}