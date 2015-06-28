#include "Program.h"
#include "../logger/GL_Logger.h"
#include "../io/TextLoader.h"
#include <easyLogging++.h>
Program::Program(std::string name):
   name(name),
   shaderProgram(0),
   vertShader(0),
   vertShaderName(""),
   fragShader(0),
   fragShaderName(""),
   geomShader(0),
   geomShaderName(""),
   tessalationShader(0),
   tessShaderName("")
{
   //No initialization yet for program
}

int Program::addVertexShader(std::string shaderSrc)
{
   vertShaderName = shaderSrc;
   return addShader(vertShader, shaderSrc, GL_VERTEX_SHADER);
}
int Program::addFragmentShader(std::string shaderSrc)
{
   fragShaderName = shaderSrc;
   return addShader(fragShader, shaderSrc, GL_FRAGMENT_SHADER);
}

int Program::addShader(GLuint & shader, std::string shaderName, GLenum shaderType)
{
   std::string shaderSrc  = TextLoader::LoadFullFile(shaderName);
   if(shaderSrc.size() > 0)
   {
      const char * shaderSrcStr= shaderSrc.c_str();
      shader = glCreateShader(shaderType);
      GL_Logger::LogError("Could not create shader buffer for " + shaderName, glGetError());
      glShaderSource(shader, 1, &shaderSrcStr, NULL);
      GL_Logger::LogError("Could not set shader source for " + shaderName, glGetError());
      glCompileShader(shader);
      return GL_Logger::CheckShader("Loading shader " + shaderName + "...", shader);
   }
   else
   {
      return -1;
   }
}

int Program::create()
{
   int err = 0;
   if(created)
   {
      LOG(WARNING) << "Program has already been created!";
      return 0;
   }
   if(vertShader > 0 && fragShader > 0)
   {
      shaderProgram = glCreateProgram();
      err |= GL_Logger::LogError("Could not create program" + name, glGetError());
      glAttachShader(shaderProgram,vertShader);
      err |= GL_Logger::LogError("Could not attatch vertex shader to program" + name, glGetError());
      glAttachShader(shaderProgram,fragShader);
      err |= GL_Logger::LogError("Could not attatch fragment shader to program" + name, glGetError());
      if(geomShader > 0)
      {
         glAttachShader(shaderProgram,geomShader);
         err |= GL_Logger::LogError("Could not attatch geometry shader to program" + name, glGetError());

      }
      if(tessalationShader > 0)
      {
         glAttachShader(shaderProgram, tessalationShader);
         err |= GL_Logger::LogError("Could not attatch fragment shader to program" + name, glGetError());

      }
      //If nothing has caused an error yet, link the program.
      if(!err)
      {
         glLinkProgram(shaderProgram);
         err |= GL_Logger::CheckProgram("Linking program " +name, shaderProgram);
         //Cleanup
         glDeleteShader(vertShader);
         err |= GL_Logger::LogError("Could not delete " + vertShaderName + "in " +name, glGetError());
         glDeleteShader(fragShader);
         err |= GL_Logger::LogError("Could not delete " + fragShaderName + "in " +name, glGetError());

         if(geomShader)
         {
            glDeleteShader(geomShader);
            err |= GL_Logger::LogError("Could not delete " + geomShaderName + "in " +name, glGetError());

         }
         if(tessalationShader > 0)
         {
            glDeleteShader(tessalationShader);
            err |= GL_Logger::LogError("Could not delete " + tessShaderName + "in " +name, glGetError());

         }
         created = true;
         return err == 0;
      }
      else
      {
         return -1;
      }
   }
   else
   {
      LOG(ERROR) << "Program "+name+" does not have a vertex and fragment stage.";
      return -1;
   }
}

void Program::enable()
{
   glUseProgram(shaderProgram);
   GL_Logger::LogError("Could not enable program " + name, glGetError());
   
}
void Program::disable()
{
   glUseProgram(0);
}

