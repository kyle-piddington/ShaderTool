#include <easylogging++.h>
#include "GL_Logger.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

inline int GL_Logger::LogError( std::string description, GLenum error)
{

   switch(error){
      case(GL_NO_ERROR):
         return 0;
         break;
      case(GL_INVALID_ENUM):
         LOG(ERROR) << description << ": GL_INVALID_ENUM";
         return -1;
         break;
      case(GL_INVALID_VALUE):
         LOG(ERROR) << description << ": GL_INVALID_VALUE";
         return -1;
         break;
      case(GL_INVALID_OPERATION):
         LOG(ERROR) << description << ": GL_INVALID_OPERATION";
         return -1;
         break;
      case(GL_INVALID_FRAMEBUFFER_OPERATION):
         LOG(ERROR) << description << ": GL_INVALID_FRAMEBUFFER_OPERATION";
         return -1;
         break;
      case(GL_OUT_OF_MEMORY):
         LOG(ERROR) << description << ": GL_OUT_OF_MEMORY";
         return -1;
         break;
      default:
         LOG(ERROR) << description << ": Unknown error!";
         return -2;
   }
};

int GL_Logger::CheckShader(std::string description, GLuint shader)
{
   GLchar * infoLog;
   GLint infoLogLen = 0;
   GLint charsWritten = 0;

   GLint compilationSuccess;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationSuccess);
   GL_Logger::LogError("Get shader compilation status", glGetError());
   if(compilationSuccess == GL_FALSE)
   {
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
      GL_Logger::LogError("get info log", glGetError());

      if(infoLogLen > 0)
      {
         infoLog = (GLchar * ) malloc(infoLogLen);
         if(infoLog == NULL)
         {
            LOG(ERROR) << "Could not allocate infolog";
            return -1;
         }
         glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
         LOG(ERROR) << description << ": Error compiling shader" << std::endl << infoLog << std::endl;
         free(infoLog);
      }
      return -1;
   
   }
   else
   {
      LOG(INFO) << description << ": Success!";
      return 0;
   }
}

int GL_Logger::CheckProgram(std::string description, GLuint shader)
{
   GLint success;
   GLchar * infoLog;
   GLint infoLogLen = 0;
   GLint charsWritten = 0;


   glGetProgramiv(shader, GL_LINK_STATUS, &success);
   GL_Logger::LogError("Get shader program creation", glGetError());
   if(success == GL_FALSE)
   {
      LOG(ERROR) << "Could not link program";
      glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
      GL_Logger::LogError("get program info log", glGetError());

      if(infoLogLen > 0)
      {
         infoLog = (GLchar * ) malloc(infoLogLen);
         if(infoLog == NULL)
         {
            LOG(ERROR) << "Could not allocate infolog";
            return -1;
         }
         glGetShaderInfoLog(shader, infoLogLen, &charsWritten, infoLog);
         LOG(ERROR) << description << ": Error compiling shader" << std::endl << infoLog << std::endl;
         free(infoLog);
      }
      return -1;
   }
   else
   {
      LOG(INFO) << description << ": Success!";
      return 0;
   }
}