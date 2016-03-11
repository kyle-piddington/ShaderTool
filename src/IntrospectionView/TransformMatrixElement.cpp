#include "TransformMatrixElement.h"
#include <imgui.h>
TransformMatrixElement::TransformMatrixElement(std::shared_ptr<UniformObject> obj):
   ProgramManagerElement(obj->getName()),
   boundObject(obj),
   pos(glm::vec3(0)),
   rot(glm::vec3(0)),
   dirty(true),
   scl(glm::vec3(1.0))
{
   t.setPosition(this->pos);
   t.setRotation(this->rot);
   t.setScale(this->scl);

}

void TransformMatrixElement::render()
{
  
   ImGui::BeginGroup();
   ImGui::Indent();
   if(ImGui::DragFloat3((boundObject->getName() + "_position").c_str(),glm::value_ptr(this->pos),0.01f))
   {
      dirty = true;
   }
   if(ImGui::DragFloat3((boundObject->getName() + "_rotation").c_str(),glm::value_ptr(this->rot),0.01f))
   {
      dirty = true;
   }
   if(ImGui::DragFloat3((boundObject->getName() + "_scale").c_str(),glm::value_ptr(this->scl),0.01f))
   {
      dirty = true;
   }
   ImGui::Unindent();
   ImGui::EndGroup();
   if(dirty)
   {
      dirty = false;
      t.setPosition(this->pos);
      t.setRotation(this->rot);
      t.setScale(this->scl);
      boundObject->bind(t.getMatrix());
   }
}