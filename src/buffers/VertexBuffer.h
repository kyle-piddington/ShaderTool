#ifndef __VERTEX_BUFFER_H__
#define __VERTEX_BUFFER_H__ value

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
class VertexBuffer
{
public:
   /**
    * Create a new Vertex buffer. This method creates a buffer on the GPU.
    */
   VertexBuffer();

   ~VertexBuffer();
   /**
    * Set the data of this buffer to a raw float array (xyz organized)
    * @param vertices pointer to the array
    * @param size     size of the array
    * @param usage    Enum for drawing. use GL_STATIC_DRAW, GL_DYNAMIC_DRAW, or GL_STREAM_DRAW depending on needs.
    */
   void setData(const float * vertices, int size, GLenum usage = GL_STATIC_DRAW);
   /**
    * set the data of this buffer from a standard vector (xyz organized)
    * @param vertices The vertices to send to the GPU
    * @param usage    Enum for drawing. Use GL_STATIC_DRAW, GL_DYNAMIC_DRAW< or GL_STREAM_DRAW.
    */
   template<typename T>
   void setData(const std::vector<T> & vertices, GLenum usage = GL_STATIC_DRAW);

   /**
    * Bind this buffer to the GPU. Be sure to unbind it later!
    */
   void bind();
   /**
    * Unbind the buffer from the GPU.
    */
   void unbind();

   /**
    * Get the number of vectors bound 
    * @param  floatsPerVert [description]
    * @return               [description]
    */
   int getNumVerts (int floatsPerVert = 3) const
   {
      return vertsLen / floatsPerVert;
   }
private:
   GLuint vboID;
   int vertsLen;

};

#endif