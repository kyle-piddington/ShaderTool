#include "Vec3Element.h"
#include "imgui.h"
Vec3Element::Vec3Element(std::shared_ptr<Vec3ObjectController> controller):
   ProgramManagerElement(controller->getName()),
   ctrl(controller)
{

}
void Vec3Element::render()
{
   glm::vec3 val = ctrl->getVec3();
   if(ImGui::DragFloat3(ctrl->getName().c_str(),glm::value_ptr(val),0.01f))
   {
      ctrl->bind(val);
   }
}