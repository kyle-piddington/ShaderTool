#include "VertexBuffer.h"
#include "../logger/GL_Logger.h"
#include <easylogging++.h>
VertexBuffer::VertexBuffer():
   vboID(0)
{
   glGenBuffers(1, &vboID);
   GL_Logger::LogError("Initialize VBO", glGetError());
}

VertexBuffer::~VertexBuffer()
{
   glDeleteBuffers(1,&vboID);
   GL_Logger::LogError("Deinitialize VBO", glGetError());
}

void VertexBuffer::setData(const float * vertices, int size, GLenum usage)
{
   if(vboID == 0)
   {
      LOG(ERROR) << "Vertex buffer not initialized";
   }
   else
   {
      glBindBuffer(GL_ARRAY_BUFFER, vboID);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, usage);
      GL_Logger::LogError("Could not bind data to Vertex Buffer", glGetError());
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }
}
void VertexBuffer::setData(const std::vector<float>  & vertices ,  GLenum usage)
{
   if(vboID > 0)
   {
      LOG(ERROR) << "Vertex buffer not initialized";
   }
   else
   {
      glBindBuffer(GL_ARRAY_BUFFER, vboID);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], usage);
      GL_Logger::LogError("Bind data to Vertex Buffer", glGetError());
      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }
}

void VertexBuffer::bind()
{
   glBindBuffer(GL_ARRAY_BUFFER, vboID);
   GL_Logger::LogError("Could not bind vertex buffer", glGetError());
}

void VertexBuffer::unbind()
{
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}