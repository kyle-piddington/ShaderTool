#include "Scene.h"

Scene::Scene(Context * context)
{
   if(context != nullptr)
      ctx = context;
}
Scene::~Scene()
{
   this->cleanup();
   for (std::vector<Program *>::iterator i = requiredPrograms.begin(); i != requiredPrograms.end(); ++i)
   {
      if(*i != nullptr)
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

Context * Scene::getContext()
{
   return ctx;
}

void Scene::setContext(Context * context)
{
   this->ctx = context;
}


/**
 * Add Time, iGlobalTime, iWindowResolution
 */
void Scene::initGlobalUniforms()
{
   for (std::vector<Program *>::iterator i = requiredPrograms.begin(); i != requiredPrograms.end(); ++i)
   {
      std::cout << "Trying to add uniform" << std::endl; 
      if((*i)->hasUniform("iGlobalTime"))
         (*i)->addUniform("iGlobalTime");
      if((*i)->hasUniform("iWindowResolution"))
      {
         (*i)->addUniform("iWindowResolution");
         (*i)->enable();
         (*i)->getUniform("iWindowResolution").bind(glm::vec2(getContext()->getWindowWidth(),getContext()->getWindowHeight()));
      }
   }
   glUseProgram(0);
}
void Scene::updateGlobalUniforms()
{
   for (std::vector<Program *>::iterator i = requiredPrograms.begin(); i != requiredPrograms.end(); ++i)
   {
      if((*i)->hasUniform("iGlobalTime"))
      {
         GLSLParser::UniformObject timeObj = (*i)->getUniform("iGlobalTime");
         if(timeObj.isValid())
         {

            (*i)->enable();
            timeObj.bind(glfwGetTime());

         }
      }
   }
   glUseProgram(0);
}