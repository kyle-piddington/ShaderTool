#ifndef __ELEMENT_BUFFER_OBJECT_H__
#define __ELEMENT_BUFFER_OBJECT_H__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

/**
 * A C++ wrapper around an openGL EBO. Provides methods to push data into a buffer.
 */
class ElementBufferObject
{
public:
   /**
    * Create a new Vertex buffer. This method creates a buffer on the GPU.
    */
   ElementBufferObject();

   ~ElementBufferObject();
   /**
    * Set the data of this buffer to a raw float array (xyz organized)
    * @param vertices pointer to the array
    * @param size     size of the array
    * @param usage    Enum for drawing. use GL_STATIC_DRAW, GL_DYNAMIC_DRAW, or GL_STREAM_DRAW depending on needs.
    */
   void setData(const unsigned int * indicies, int size, GLenum usage = GL_STATIC_DRAW);
   /**
    * set the data of this buffer from a standard vector (xyz organized)
    * @param vertices The vertices to send to the GPU
    * @param usage    Enum for drawing. Use GL_STATIC_DRAW, GL_DYNAMIC_DRAW< or GL_STREAM_DRAW.
    */
   void setData(const std::vector<unsigned int> & indicies, GLenum usage = GL_STATIC_DRAW);

   /**
    * Bind this buffer to the GPU. Be sure to unbind it later!
    */
   void bind();
   /**
    * Unbind the buffer from the GPU.
    */
   void unbind();

   /**
    * Get the number of indicies
    */
   int getNumIndicies() const
   {
      return numInds;
   }
private:
   GLuint eboID;
   int numInds;

};
#endif