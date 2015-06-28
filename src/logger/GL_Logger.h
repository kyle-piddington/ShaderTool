#ifndef __GL_LOGGER_H__
#define __GL_LOGGER_H__
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>

class GL_Logger
{
public:
   static int LogError(std::string description, GLenum error);
   static int CheckShader(std::string description, GLuint shader);
   static int CheckProgram(std::string description, GLuint shader);

};
#endif