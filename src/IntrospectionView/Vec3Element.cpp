#include "Vec3Element.h"
#include "imgui.h"
Vec3Element::Vec3Element(std::shared_ptr<UniformObjectController> controller):
   ProgramManagerElement(controller->getName()),
   ctrl(controller)
{

}
void Vec3Element::render()
{
   if(ImGui::DragFloat3(ctrl->getName().c_str(),glm::value_ptr(this->vector),0.01f))
   {
      ctrl->bind(vector);
   }
}