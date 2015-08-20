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
   tessShaderName(""),
   created(false)
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
         if(err == 0)
         {


            created = true;
            return 0;
         }
         else
         {
            return -1;
         }

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

int Program::addAttribute(std::string attribName)
{
   if(!created)
   {
      LOG(ERROR) << "Program " + name + " has not been created. Call .create()";
      return -1;
   }
   GLint atrbId = glGetAttribLocation(shaderProgram, attribName.c_str());
   GL_Logger::LogError("Could not search program " + name, glGetError());
   if(atrbId == -1)
   {
      LOG(WARNING) << "Program " + name +  " Could not bind attribute " + attribName + " (It may not exist, or has been optimized away)";
      return -1;
   }
   else
   {
      attributes[attribName] = atrbId;
   }
   return 0;
}

int Program::addUniform(std::string uniformName)
{
   if(!created)
   {
      LOG(ERROR) << "Program " + name + " has not been created. Call .create()";
      return -1;
   }
   GLint unifId = glGetUniformLocation(shaderProgram, uniformName.c_str());
   GL_Logger::LogError("Could not search program " + name, glGetError());
   if(unifId == -1)
   {
      LOG(WARNING) << "Program " + name +  " Could not bind uniform " + uniformName + " (It may not exist, or has been optimized away)";
      return -1;
   }
   else
   {
      uniforms[uniformName] = unifId;
   }
   return 0;
}

GLint Program::getAttribute(std::string attribName)
{
   if(!created)
   {
      LOG(ERROR) << "Program " + name + " has not been created. Call .create()";
      return -1;
   }
   auto attributeId = attributes.find(attribName);
   if(attributeId == attributes.end())
   {
      LOG(WARNING) << "Program " + name + " has no attribute named " + attribName + " (Did you forget to add it to the program?)";
      return -1;
   }
   else
   {
      boundAttributes[attribName] = true;
      return attributeId->second;
   }

}

GLint Program::getUniform(std::string unifName)
{
   if(!created)
   {
      LOG(ERROR) << "Program" + name + " has not been created. Call .create()";
      return -1;
   }
   auto unifId = uniforms.find(unifName);
   if(unifId == uniforms.end())
   {
      LOG(WARNING) << "Program " + name + " has no attribute named " + unifName + " (Did you forget to add it to the program?)";
      return -1;
   }
   else
   {
      boundUniforms[unifName] = true;
      return unifId->second;
   }
}

bool Program::checkBoundVariables()
{
   if(!created)
   {
      LOG(ERROR) << "Program" + name + " has not been created. Call .create()";
      return -1;
   }
   bool allBound = true;
   for (auto i = attributes.begin(); i != attributes.end(); ++i)
   {
      allBound &= (boundAttributes.find((*i).first) != boundAttributes.end());
   }
   for (auto i = uniforms.begin(); i != uniforms.end(); ++i)
   {
      allBound &= (boundUniforms.find((*i).first) != boundUniforms.end());
   }
   return allBound;
}
int Program::addUniformStruct(std::string name, GL_Structure &  glStruct)
{
   std::vector<std::string> uniformNames = glStruct.getUniformNames();
   int canAddUniform = 0;
   for (std::vector<std::string>::iterator i = uniformNames.begin(); i != uniformNames.end(); ++i)
   {
      canAddUniform |= addUniform(name + "." +*i);
   }
   //If all uniforms were successfully added
   if(canAddUniform == 0)
   {
      for (std::vector<std::string>::iterator i = uniformNames.begin(); i != uniformNames.end(); ++i)
      {
         glStruct.setUniformLocation(*i,getUniform(name + "." +*i));
      }
      return 0;
   }
   else
   {
      LOG(ERROR) << "Struct " + name + " Could not find all attributes!"; 
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

