#include "Vec3Element.h"
#include "imgui.h"
Vec3Element::Vec3Element(std::shared_ptr<UniformObject> object):
   ProgramManagerElement(object->getName()),
   boundObject(object)
{

}
void Vec3Element::render()
{
   if(ImGui::DragFloat3(boundObject->getName().c_str(),glm::value_ptr(this->vector),0.01f))
   {
      boundObject->bind(vector);
   }
}