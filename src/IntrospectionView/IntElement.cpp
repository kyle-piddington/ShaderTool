#include "IntElement.h"
#include <imgui.h>
IntElement::IntElement(std::shared_ptr<IntObjectController> controller):
   ProgramManagerElement(controller->getName()),
   ctrl(controller)
{

}

void IntElement::render()
{
   int val = ctrl->getInt();
   if(ImGui::DragInt(ctrl->getName().c_str(),&val,0.2))
   {
      ctrl->bind(val);
   }
}