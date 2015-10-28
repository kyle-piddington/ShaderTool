#include "VertexArrayObject.h"

#include "../logger/GL_Logger.h"
VertexArrayObject::VertexArrayObject()
{
   glGenVertexArrays(1, &vaoID);
   GL_Logger::LogError("Initialize VAO", glGetError());
   std::cout << "Created VAO @" << vaoID << std::endl;
}

VertexArrayObject::~VertexArrayObject()
{
   glDeleteVertexArrays(1, &vaoID);
   GL_Logger::LogError("Delete VAO", glGetError());
}

void VertexArrayObject::addAttribute(GLuint location, VertexBuffer & bfr, GLint stride, GLint offset,  GLint size, GLboolean normalized, GLenum type)
{
   //bind VAO
   glBindVertexArray(vaoID);
   bfr.bind();
   GL_Logger::LogError("Initialize VAO", glGetError());
  
   if(type == GL_FLOAT)
   {
      glVertexAttribPointer(location, size, type, normalized, stride, (const GLvoid *) offset);
      GL_Logger::LogError("Initialize VAO", glGetError());
  
   }
   else if(type == GL_INT)
   {
      glVertexAttribIPointer(location,size,type,stride,(GLvoid *) offset);
       GL_Logger::LogError("Initialize VAO", glGetError());
  
   }
   glEnableVertexAttribArray(location);
   GL_Logger::LogError("Initialize VAO", glGetError());
  
   glBindVertexArray(0);
   GL_Logger::LogError("Initialize VAO", glGetError());
   locations.push_back(location);
}



void VertexArrayObject::addElementArray(ElementBufferObject & ebo)
{
   glBindVertexArray(vaoID);
   ebo.bind();
   GL_Logger::LogError("Add Element Array Object" ,glGetError());
   glBindVertexArray(0);
}
void VertexArrayObject::enableLocation(GLuint location)
{
   glBindVertexArray(vaoID);
   glEnableVertexAttribArray(location);
   GL_Logger::LogError("Could not enable VAO location", glGetError());
   glBindVertexArray(0);

}

void VertexArrayObject::disableLocation(GLuint location)
{
   glBindVertexArray(vaoID);
   glDisableVertexAttribArray(location);
   glBindVertexArray(0);
}



void VertexArrayObject::bind()
{
   glBindVertexArray(vaoID);
   GL_Logger::LogError("Could not bind VAO at "+std::to_string(vaoID), glGetError());
   
}
void VertexArrayObject::unbind()
{
   glBindVertexArray(0);
}