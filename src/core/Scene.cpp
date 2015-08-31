#include "Scene.h"

Scene::Scene()
{

}
Scene::~Scene()
{
   this->cleanup();
   for (std::vector<Program *>::iterator i = requiredPrograms.begin(); i != requiredPrograms.end(); ++i)
   {
      delete *i;
   }
}

bool Scene::canRenderScene()
{
   bool canRender = true;
   for (std::vector<Program *>::iterator i = requiredPrograms.begin(); i != requiredPrograms.end(); ++i)
   {
      canRender &= (*i)->isCreated();
   }
   return canRender;
}

bool Scene::shouldReloadScene()
{
   bool shouldReload = false;
   for (std::vector<Program *>::iterator i = requiredPrograms.begin(); i != requiredPrograms.end(); ++i)
   {
      shouldReload |= (*i)->shouldProgramRecompile();
   }
   return shouldReload;
}

bool Scene::compilePrograms()
{
   int badProgram = 0;
   for (std::vector<Program *>::iterator i = requiredPrograms.begin(); i != requiredPrograms.end(); ++i)
   {
      badProgram |= (*i)->create();
   }
   if(badProgram)
   {
      return false;
   }
   return true;
}

void Scene::cleanup()
{

}

Program * Scene::createProgram(std::string programName)
{
   Program * prog = new Program(programName);
   requiredPrograms.push_back(prog);
   return prog;
}