#include "ElementBufferObject.h"
#include "../logger/GL_Logger.h"
#include <easylogging++.h>
ElementBufferObject::ElementBufferObject():
   eboID(0)
{
   glGenBuffers(1, &eboID);
   GL_Logger::LogError("Initialize EBO", glGetError());
}

ElementBufferObject::~ElementBufferObject()
{
   /**
    * Deconstruct later if handled by VAO.
    */
   //glDeleteBuffers(1,&eboID);
   //GL_Logger::LogError("Deinitialize EBO", glGetError());
}

void ElementBufferObject::setData(const unsigned int * indicies, int size, GLenum usage)
{
   if(eboID == 0)
   {
      LOG(ERROR) << "Element buffer not initialized";
   }
   else
   {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * size, indicies, usage);
      GL_Logger::LogError("Could not bind data to index Buffer", glGetError());
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }
}
void ElementBufferObject::setData(const std::vector<unsigned int>  & indicies ,  GLenum usage)
{
   if(eboID > 0)
   {
      LOG(ERROR) << "index buffer not initialized";
   }
   else
   {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicies.size(), &indicies[0], usage);
      GL_Logger::LogError("Bind data to index Buffer", glGetError());
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }
}

void ElementBufferObject::bind()
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
   GL_Logger::LogError("Could not bind index buffer", glGetError());
}

void ElementBufferObject::unbind()
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}