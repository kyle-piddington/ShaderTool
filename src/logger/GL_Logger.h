#ifndef __GL_LOGGER_H__
#define __GL_LOGGER_H__
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>

class GL_Logger
{
public:

   static int LogError(std::string description, GLenum error);
   /**
    * Check to see if a shader was compiled successfully
    * @param  description  Description of the shader action
    * @param  shader      Shader to check
    * @return             0 if OK, -1 otherwise
    */
   static int CheckShader(std::string description, GLuint shader);
   /**
    * Check the status of a program
    * @param Description Description of the action before this log
    * @param	program 	the program's ID on the GPU.
    * @return	0 of OK, -1 otherwise.
    */
   static int CheckProgram(std::string description, GLuint program);

};
#endif