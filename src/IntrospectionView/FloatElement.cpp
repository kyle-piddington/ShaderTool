#include "FloatElement.h"
#include <imgui.h>
FloatElement::FloatElement(std::shared_ptr<FloatObjectController> controller):
   ProgramManagerElement(controller->getName()),
   ctrl(controller)
{

}

void FloatElement::render()
{
   float val = ctrl->getFloat();
   if(ImGui::DragFloat(ctrl->getName().c_str(),&val,0.01))
   {
      ctrl->bind(val);
   }
}