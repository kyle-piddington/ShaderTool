#include "ProgramManagerWindow.h"
#include "imgui.h"
#include "ProgramManagerElementFactory.h"
ProgramManagerWindow::ProgramManagerWindow():
   manager(nullptr)
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

void ProgramManagerWindow::refresh()
{
   /**
    * First, clear out the old windows
    */
   elements.clear();
   /**
    * Get all the uniforms in the program.
    */
   if(this->manager != nullptr)
   {
      auto uniforms = manager->getActiveProgram()->getAllActiveUniforms();

      for(auto uniformObject : uniforms)
      {
         /*
         std::shared_ptr<ProgramManagerElement> element = ProgramManagerElementFactory::Create(uniformObject);
         if(element != nullptr)
         {
            elements.push_back(element);

         }
         */
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
      ImGui::Text(("Current shader program: " + manager->getVertexName()).c_str());
      ImGui::Text(("Current fragment program: " + manager->getFragmentName()).c_str());
      if(ImGui::Button("Recompile"))
      {
        if(manager->reload())
        {
          refresh();
        };

      }
      for(auto element : elements)
      {
         element->render();
      }
      ImGui::End();
   }
}