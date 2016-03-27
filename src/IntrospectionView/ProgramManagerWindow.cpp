#include "ProgramManagerWindow.h"
#include "imgui.h"
#include "ProgramManagerElementFactory.h"
ProgramManagerWindow::ProgramManagerWindow():
   manager(nullptr),
   modelMgr(nullptr)
{

}

ProgramManagerWindow::~ProgramManagerWindow()
{

}
void ProgramManagerWindow::setProgramManager(ToolSceneProgramManager * mgr)
{
   this->manager = mgr;
   refresh();
}

void ProgramManagerWindow::setModelManager(ModelManager * mgr)
{
  this->modelMgr = mgr;
}
void ProgramManagerWindow::refresh()
{
   /**
    * First, clear out the old windows
    */
   elements.clear();
   modelElement = nullptr;
   /**
    * Get all the uniforms in the program.
    */
   if(this->manager != nullptr)
   {
      /** Get model manager*/
      std::shared_ptr<UniformObjectController> modelCtrl =
         manager->getModelUniformController();
      if(modelCtrl != nullptr)
      {
         modelElement = std::make_shared<TransformMatrixElement>(
               std::static_pointer_cast<TransformController>(modelCtrl));
      }
      auto uniforms = manager->getExposedUniformControllers();
      for(auto uniformObject : uniforms)
      {

         std::shared_ptr<ProgramManagerElement> element = ProgramManagerElementFactory::Create(uniformObject);
         if(element != nullptr)
         {
            elements.push_back(element);

         }

      }
   }
   /**
    * Sort the element list
    */
   std::sort(elements.begin(),elements.end(), [](std::shared_ptr<ProgramManagerElement> a,
                                                std::shared_ptr<ProgramManagerElement> b)
   {
      return a->getName() < b->getName();
   });
}
void ProgramManagerWindow::render()
{
   if(manager != nullptr)
   {


      ImGui::Begin("Program Management");

      renderProgramManager();

      if(ImGui::Button("Recompile"))
      {
        if(manager->reload())
        {
          refresh();
        };
      }
      if(ImGui::CollapsingHeader("Model Management"))
      {
        renderModelManager();
        if(modelElement != nullptr)
        {
           modelElement->render();
        }

      }
      if(ImGui::CollapsingHeader("Uniforms",NULL,true,true))
      {
        for(auto element : elements)
        {
           element->render();
        }
      }
      ImGui::End();
   }
}

void ProgramManagerWindow::renderModelManager()
{
  //Get the current list of avaliable models:
  if(modelMgr != nullptr)
  {

    std::vector<std::string> models = modelMgr->getModelNames();
    std::string cModel = modelMgr->getActiveModelName();

    int selected = std::find(models.begin(),models.end(), cModel) - models.begin();
    /**
     * Build char ** ptr
     */
    const char * mNames[models.size()];
    for(int i = 0; i < models.size(); i++)
    {
      mNames[i] = models[i].c_str();
    }
    if(ImGui::Combo("Model",&selected, mNames, models.size()))
    {
      modelMgr->load(models[selected]);
    }
  }

}

void ProgramManagerWindow::renderProgramManager()
{
  //Get the current list of avaliable shaders:
  if(manager != nullptr)
  {

    std::vector<std::string> vertShaders = manager->getVertexShaderNames();
    std::string cVertShader = manager->getVertexName();

    int vSelected = std::find(vertShaders.begin(),vertShaders.end(), cVertShader) - vertShaders.begin();
    /**
     * Build char ** ptr
     */
    const char * vNames[vertShaders.size()];
    for(int i = 0; i < vertShaders.size(); i++)
    {
      vNames[i] = vertShaders[i].c_str();
    }
    if(ImGui::Combo("Vertex Shader",&vSelected, vNames, vertShaders.size()))
    {
      manager->setVertexShader(vertShaders[vSelected]);
    }

    //Do same thing for frag shader.
    //
    std::vector<std::string> fragShaders = manager->getFragmentShaderNames();
    std::string cFragShader = manager->getFragmentName();
    int fSelected = std::find(fragShaders.begin(),fragShaders.end(), cFragShader) - fragShaders.begin();
    /**
     * Build char ** ptr
     */
    const char * fNames[fragShaders.size()];
    for(int i = 0; i < fragShaders.size(); i++)
    {
      fNames[i] = fragShaders[i].c_str();
    }
    if(ImGui::Combo("Fragment Shader",&fSelected, fNames, fragShaders.size()))
    {
      manager->setFragmentShader(fragShaders[fSelected]);
    }
  }


}