#include "VertexArrayObject.h"
#include "../logger/GL_Logger.h"
VertexArrayObject::VertexArrayObject()
{
   glGenVertexArrays(1, &vaoID);
   GL_Logger::LogError("Initialize VAO", glGetError());
}

VertexArrayObject::~VertexArrayObject()
{
   glDeleteVertexArrays(1, &vaoID);
   GL_Logger::LogError("Delete VAO", glGetError());
}

void VertexArrayObject::addAttribute(GLuint location, VertexBuffer & bfr, GLint size, GLint stride, GLboolean normalized)
{
   //bind VAO
   glBindVertexArray(vaoID);
   bfr.bind();
   glVertexAttribPointer(location, size, GL_FLOAT, normalized, stride * sizeof(float), (GLvoid *) 0);
   glEnableVertexAttribArray(location);
   glBindVertexArray(0);
   GL_Logger::LogError("Initialize VAO", glGetError());
   this->stride = stride;
   this->normalized = normalized;
   locations.push_back(location);
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
   GL_Logger::LogError("Could not bind VAO", glGetError());
   
}
void VertexArrayObject::unbind()
{
   glBindVertexArray(0);
}