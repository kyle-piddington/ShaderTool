#ifndef __VERTEX_ARRAY_OBJECT_H__
#define __VERTEX_ARRAY_OBJECT_H__

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "VertexBuffer.h"
#include "ElementBufferObject.h"
class VertexArrayObject
{
public:
   VertexArrayObject();
   ~VertexArrayObject();
   /**
    * Initialize the VAO
    * @param location   The shader location 
    * @param bfr        the buffer to bind
    * @param stride     the stride of the buffer
    * @param normalized normalize the buffer
    */
   void addAttribute(GLuint location, VertexBuffer & bfr,  GLint stride = 3 * sizeof(float), GLint offset = 0, GLint size = 3, GLboolean normalized = GL_FALSE, GLenum type = GL_FLOAT);

   /**
    * Add an element array to the VAO
    * @param ebo        The buffer to add.
    */
   void addElementArray(ElementBufferObject & ebo);
   /**
    * Set the location of the VAO
    * @param location the location in the shader
    */
   void enableLocation(GLuint location);
   

   /**
    * Disable a location in the vao
    */
   void disableLocation(GLuint location);
   /**
    * Bind the vertex array object. Make sure to unbind afterwords
    */
   void bind();
   /**
    * Unbind the vertex array object
    */
   void unbind();

private:
   int stride;
   GLboolean normalized;
   GLuint vaoID;
   std::vector<GLuint> locations;
};
#endif