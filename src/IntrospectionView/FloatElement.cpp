#include "FloatElement.h"
#include <imgui.h>
FloatElement::FloatElement(std::shared_ptr<UniformObject> obj):
   ProgramManagerElement(obj->getName()),
   boundObject(obj),
   flt(0.0)
{

}

void FloatElement::render()
{
   if(ImGui::DragFloat(boundObject->getName().c_str(),&flt,0.01))
   {
      boundObject->bind(flt);
   }
}