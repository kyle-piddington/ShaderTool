#include "ModelManager.h"

ModelManager::ModelManager()
{

}
void ModelManager::setModel(std::shared_ptr<Model> mdl)
{
   this->mdl = mdl;
}
void ModelManager::render(std::shared_ptr<Program> program)
{
   mdl->render(*program);
}