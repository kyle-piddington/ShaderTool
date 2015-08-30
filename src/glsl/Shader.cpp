#include "GL_Logger.h"
#include "Shader.h"
#include "Textloader.h"

Shader::Shader(std::string path, GLenum shaderType): ReloadableAsset(path),
path(path),
shaderID(0),
shaderType(shaderType),
isShaderCompiled(false)
{

}

Shader::~Shader()
{

}
int Shader::compile()
{
   isShaderCompiled = false;
   //Create shader ID
   if(shaderID == 0)
   {

      shaderID = glCreateShader(shaderType);
      int err = GL_Logger::LogError("Could not create shader buffer for " + path, glGetError());

      if(err == -1)
      {
         return -1;
      }
   }
   std::string shaderSrc  = TextLoader::LoadFullFile(path);
   if(shaderSrc.size() > 0)
   {
      const char * shaderSrcStr= shaderSrc.c_str();
      glShaderSource(shaderID, 1, &shaderSrcStr, NULL);
      GL_Logger::LogError("Could not set shader source for " + path, glGetError());
      glCompileShader(shaderID);
      if(GL_Logger::CheckShader("Loading shader " + path + "...", shaderID) == 0)
      {
         isShaderCompiled=true;
      }
      return 0;
   }
   else
   {
      return -1;
   }
}
//Mark shader as not compiled
void Shader::reload()
{
   isShaderCompiled = false;
}

bool Shader::isCompiled()
{
   return isShaderCompiled;
}

std::string Shader::getPath()
{
   return path;
}
int Shader::deleteFromGPU()
{
   if(shaderID != 0)
   {
      glDeleteShader(shaderID);
      shaderID = 0;
      return GL_Logger::LogError("Could not delete " + path,glGetError());
   }
   return 0;
}
GLuint Shader::getID()
{
   return shaderID;
}