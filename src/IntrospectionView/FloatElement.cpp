#include "FloatElement.h"
#include <imgui.h>
FloatElement::FloatElement(std::shared_ptr<UniformObjectController> controller):
   ProgramManagerElement(controller->getName()),
   ctrl(controller),
   flt(0.0)
{

}

void FloatElement::render()
{
   if(ImGui::DragFloat(ctrl->getName().c_str(),&flt,0.01))
   {
      ctrl->bind(flt);
   }
}