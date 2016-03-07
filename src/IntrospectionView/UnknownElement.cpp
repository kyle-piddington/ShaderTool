#include "UnknownElement.h"
#include <imgui.h>
UnkwownElement::UnkwownElement(std::string name):
   ProgramManagerElement(name),
   name(name)
   {

   }
void UnkwownElement::render()
{
   ImGui::TextDisabled(name.c_str());
}