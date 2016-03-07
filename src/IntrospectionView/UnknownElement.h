#ifndef __UNKNOWN_ELEMENT_H__
#define __UNKNOWN_ELEMENT_H__
#include "ProgramManagerElement.h"
/**
 * An Unkown element displays a GLSL element's name,
 * but nothing else. 
 */
class UnkwownElement : public ProgramManagerElement
{
public:
   UnkwownElement(std::string name);
   void render();
private:
   std::string name;
};
#endif