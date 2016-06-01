#ifndef __PROGRAM_MANAGER_ELEMENT_H__
#define __PROGRAM_MANAGER_ELEMENT_H__
#include <string>
class ProgramManagerElement
{
public:
   ProgramManagerElement(std::string elementName):
      elemName(elementName)
   {

   }

   virtual void render() = 0;
   const std::string & getName()
   {
      return elemName;
   }

private:
   std::string elemName;
};
#endif