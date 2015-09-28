#include "VertexBuffer.h"
#include "../logger/GL_Logger.h"
#include <easylogging++.h>
VertexBuffer::VertexBuffer():
   vboID(0)
{
   glGenBuffers(1, &vboID);
   GL_Logger::LogError("Initialize VBO", glGetError());
   std::cout << "VBO created @" << vboID << std::endl;
}

VertexBuffer::~VertexBuffer()
{
   /**
    * Deconstruct later if handled by VAO, this needs some work.
    * ARC style counting could help though!
    */
   /*
   glDeleteBuffers(1,&vboID);
   GL_Logger::LogError("Deinitialize VBO", glGetError());
   */
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
      vertsLen = size;
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

