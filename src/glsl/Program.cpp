#include "../logger/GL_Logger.h"
#include "Program.h"

#include "../io/TextLoader.h"
#include <easyLogging++.h>
#include "ShaderManager.h"
#include <GL/glew.h>
#include "UniformExtractor.h"

Program::Program(std::string name):
   name(name),
   vertShader(nullptr),
   fragShader(nullptr),
   geomShader(nullptr),
   tessalationShader(nullptr),
   created(false)
{
}
Program::~Program()
{
   if(created)
   {
      glDeleteProgram(shaderProgram);
   }

}


int Program::addVertexShader(std::string shaderSrc)
{
   return addShader(vertShader, shaderSrc, GL_VERTEX_SHADER);
}
int Program::addFragmentShader(std::string shaderSrc)
{
   return addShader(fragShader, shaderSrc, GL_FRAGMENT_SHADER);
}
int Program::addGeometryShader(std::string shaderSrc)
{
   return addShader(geomShader, shaderSrc, GL_GEOMETRY_SHADER);
}

std::string Program::getVertexShaderName() const
{
   return getShaderName(vertShader);
}

std::string Program::getFragmentShaderName() const
{
   return getShaderName(fragShader);
}
std::string Program::getGeometryShaderName() const
{
   return getShaderName(geomShader);
}
std::string Program::getTessalationShaderName() const
{
   return getShaderName(tessalationShader);
}

std::string Program::getShaderName(std::shared_ptr<Shader> shader) const
{
   return shader->getName();
}

int Program::addShader(std::shared_ptr<Shader> & shader, std::string shaderName, GLenum shaderType)
{
   shader = ShaderManager::getShader(shaderName,shaderType);
   if(shader->compile() == 0)
   {
      return 0;
   }
   else
   {
      return -1;
   }
}
int Program::compileAllShaders()
{
   int okCompiled = 0;
   if(vertShader != nullptr)
      okCompiled |=vertShader->compile();
   if(fragShader != nullptr)
      okCompiled |= fragShader->compile();
   if(geomShader != nullptr)
      okCompiled |= geomShader->compile();
   if(tessalationShader != nullptr)
      okCompiled |= tessalationShader->compile();
   return okCompiled;

}

/**
 * Create a program. report all ok if
 * @return [description]
 */
int Program::create()
{
   ProgCreationInfo programStatus = createProgram();
   if(programStatus.status == ProgramStatus::NOCHANGE)
   {
      return 0;
   }
   if(programStatus.status == ProgramStatus::LINK_ERR)
   {
      glDeleteProgram(programStatus.program);
      if(created)
      {
         LOG(WARNING) << "Program could not be created, but is already running. The progam will not be replaced.";
         return 0;
      }
   }
   else
   {
      if(programStatus.status == ProgramStatus::OK)
      {
         if(created)
         {
            glDeleteProgram(shaderProgram);
         }
         shaderProgram = programStatus.program;
         created = true;
         generateUniforms();
         /**
          * auto generate uniforms
          */
        
         return 0;
      }
      else
      {
         //Program could not compile, but is not going to fail
         if (created)
            return 0;
         else
            return -1;
      }
   }
   return -1;
}

Program::ProgCreationInfo Program::createProgram()
{
   ProgCreationInfo prog;
   prog.program = 0;
   prog.status = ProgramStatus::OK;
   int err = 0;
   //Already created case
   if(created && !shouldProgramRecompile())
   {
      LOG(WARNING) << "Program has already been created, and no changes are detected";
      prog.status = ProgramStatus::NOCHANGE;
      return prog;
   }
   //Reloading case
   else if(created && shouldProgramRecompile())
   {
      if(compileAllShaders() != 0)
      {
         prog.status = ProgramStatus::COMPILE_ERR;
         return prog;
      }
   }
   if(vertShader!= nullptr && vertShader->isCompiled() && fragShader!=nullptr && fragShader->isCompiled())
   {

      prog.program = glCreateProgram();
      err |= GL_Logger::LogError("Could not create program" + name, glGetError());
      glAttachShader(prog.program,vertShader->getID());
      err |= GL_Logger::LogError("Could not attatch vertex shader to program" + name, glGetError());
      glAttachShader(prog.program,fragShader->getID());
      err |= GL_Logger::LogError("Could not attatch fragment shader to program" + name, glGetError());
      if(geomShader!= nullptr && geomShader->isCompiled())
      {
         glAttachShader(prog.program,geomShader->getID());
         err |= GL_Logger::LogError("Could not attatch geometry shader to program" + name, glGetError());

      }
      if(tessalationShader != nullptr && tessalationShader->isCompiled())
      {
         glAttachShader(prog.program, tessalationShader->getID());
         err |= GL_Logger::LogError("Could not attatch fragment shader to program" + name, glGetError());

      }
      //If nothing has caused an error yet, link the program.
      if(!err)
      {
         glLinkProgram(prog.program);
         err |= GL_Logger::CheckProgram("Linking program " +name, prog.program);
         if(err == 0)
         {
            return prog;
         }
         else
         {
            prog.status = ProgramStatus::LINK_ERR;
            return prog;
         }

      }
      else
      {
         prog.status = ProgramStatus::LINK_ERR;
         return prog;
      }

   }
   else
   {
      LOG(ERROR) << "Program "+name+" does not have a valid vertex and fragment stage.";
      prog.status = ProgramStatus::NOT_ENOUGH_SHADERS_ERR;
      return prog;
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
      //If uniform was found before, but not on a reload, set the id to -1
      auto foundUnif = uniforms.find(uniformName);
      if(foundUnif!= uniforms.end())
      {
         foundUnif->second->setID(-1);
      }
      return -1;
   }
   else
   {
      GLuint uniformIdx;
      const char* nameCST = uniformName.c_str();
      glGetUniformIndices(shaderProgram, 1, &nameCST,
         &uniformIdx);
      GLSLType::GLSLType type = getUniformType(uniformIdx);

      auto foundUnif = uniforms.find(uniformName);
      if(foundUnif!= uniforms.end())
      {
         foundUnif->second->setID(unifId);
      }
      else
      {
         auto empl = uniforms.emplace(uniformName,std::make_shared<UniformObject>(uniformName,type,unifId));
      }
      //If Not inserting a new uniform, set the ID to -1

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
      return attributeId->second;
   }

}

const UniformObject & Program::getUniform(std::string unifName)
{
   if(!created)
   {
      LOG(ERROR) << "Program" + name + " has not been created. Call .create()";
      return UniformObject::InvalidObject;
   }
   auto unifId = uniforms.find(unifName);
   if(unifId == uniforms.end())
   {
      LOG(WARNING) << "Program " + name + " has no uniform named " + unifName + " (Did you forget to add it to the program?)";
      return UniformObject::InvalidObject;
   }
   else
   {
      return *unifId->second;
   }
}

bool Program::hasUniform(std::string unifName)
{
   if(!created)
   {
      LOG(ERROR) << "Program " + name + " has not been created. Call .create()";
      return false;
   }
   if(uniforms.find(unifName) == uniforms.end())
   {
      GLint unifId = glGetUniformLocation(shaderProgram, unifName.c_str());
      GL_Logger::LogError("Could not search program " + name, glGetError());
      if(unifId == -1)
      {
         return false;
      }
   }

   return true;
}


void Program::generateUniforms()
{
   if(!created)
   {
      LOG(ERROR) << "Program" + name + " has not been created. Call .create()";
   }
   else
   {
      UniformExtractor extractor;
      std::vector<std::shared_ptr<UniformObject> > objects = extractor.extract(shaderProgram);
      for (auto i = objects.begin(); i != objects.end(); ++i)
      {
         uniforms.emplace((*i)->getName(),*i);
      }
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

bool Program::shouldProgramRecompile()
{

   //If all shaders are compiled, and the program is linked, then it should not be compiled
   bool isCompiled = true;
   isCompiled &= (vertShader == nullptr || vertShader->isCompiled());
   isCompiled &= (fragShader == nullptr || fragShader->isCompiled());
   isCompiled &= (geomShader == nullptr || geomShader->isCompiled());
   isCompiled &= (tessalationShader == nullptr || tessalationShader->isCompiled());
   return !isCompiled;
}

bool Program::hasAddedUniform(std::string name)
{
   return(uniforms.find(name) != uniforms.end());

}

bool Program::isCreated()
{
   return created;
}


std::vector < std::shared_ptr <UniformObject> > Program::getAllActiveUniforms()
{
   std::vector< std::shared_ptr < UniformObject > > retUnifs;
   for(auto unif : uniforms)
   {
      retUnifs.push_back(unif.second);
   }
   return retUnifs;
}

GLSLType::GLSLType Program::getUniformType(GLuint id)
{
   GLenum type;
   glGetActiveUniform(  shaderProgram,
      id,
   0,
   nullptr,
   nullptr,
   &type,
   nullptr);
   GL_Logger::LogError("Could not get type of uniform");

   return GLSLType::GLEnumToGLSLType(type);
}


