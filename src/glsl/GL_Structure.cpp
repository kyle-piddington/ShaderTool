#include "GL_Structure.h"
#include <easylogging++.h>

GL_Structure::GL_Structure()
{
}

GL_Structure::GL_Structure(const GL_Structure & other)
{
   for (auto i = other.uniforms.begin(); i != other.uniforms.end(); ++i)
   {
      uniforms[i->first] = -1;
   }

}

void GL_Structure::addAttribute(std::string attribName)
{
   uniforms[attribName] = -1;
}

std::vector<std::string> GL_Structure::getUniformNames()
{
   std::vector<std::string> names;
   for (auto i = uniforms.begin(); i != uniforms.end(); ++i)
   {
      names.push_back(i->first);
   }
   return names;
}

int GL_Structure::setUniformLocation(std::string name, GLint location)
{
   auto uniformID = uniforms.find(name);
   if(uniformID == uniforms.end())
   {
      LOG(WARNING) << "Structure has no attribute named " + name + " (Did you forget to add it to the structure?)";
      return -1;
   }
   uniformID->second = location;
   return 0;
}
GLint GL_Structure::get(std::string name)
{
   auto uniformID = uniforms.find(name);
   if(uniformID == uniforms.end())
   {
      LOG(WARNING) << "Structure has no attribute named " + name + " (Did you forget to add it to the structure?)";
      return -1;
   }
   if(uniformID->second == -1)
   {
      LOG(WARNING) << "Attribute " + name +" is in strucutre, but not bound.";
   }
   return uniformID->second;
}
