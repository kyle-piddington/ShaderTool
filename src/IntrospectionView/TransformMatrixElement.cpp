#include "TransformMatrixElement.h"
#include <imgui.h>
#include "Transform.h"
TransformMatrixElement::TransformMatrixElement(std::shared_ptr<TransformController> controller):
   ProgramManagerElement(controller->getName()),
   ctrl(controller),
   pos(glm::vec3(0)),
   rot(glm::vec3(0)),
   dirty(true),
   scl(glm::vec3(1.0))
{
   Transform t = ctrl->getTransform();
   this->pos = t.getPosition(Space::LOCAL);
   this->rot = t.getRotationEuler();
   this->scl = t.getScale();
}

void TransformMatrixElement::render()
{
  
   ImGui::BeginGroup();
   ImGui::Indent();
   Transform t = ctrl->getTransform();
  
   this->pos = t.getPosition(Space::LOCAL);
   this->rot = t.getRotationEuler();
   this->scl = t.getScale();
   if(ImGui::DragFloat3((ctrl->getName() + "_position").c_str(),glm::value_ptr(this->pos),0.01f))
   {
      dirty = true;
   }
   if(ImGui::DragFloat3((ctrl->getName() + "_rotation").c_str(),glm::value_ptr(this->rot),0.01f))
   {
      dirty = true;
   }
   if(ImGui::DragFloat3((ctrl->getName() + "_scale").c_str(),glm::value_ptr(this->scl),0.01f))
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
      ctrl->bind(t);
   }
}
