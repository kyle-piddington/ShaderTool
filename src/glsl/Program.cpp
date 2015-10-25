#include "../logger/GL_Logger.h"
#include "Program.h"

#include "../io/TextLoader.h"
#include <easyLogging++.h>
#include "ShaderManager.h"


Program::Program(std::string name):
   name(name),
   vertShader(nullptr),
   fragShader(nullptr),
   geomShader(nullptr),
   tessalationShader(nullptr),
   created(false)
{
   emptyUniformArray.isValid = false;
   emptyStructUniformArray.isValid = false;
   //No initialization yet for program
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
         foundUnif->second.setID(-1);
      }
      return -1;
   }
   else
   {
      GLuint uniformIdx;
      const char* nameCST = uniformName.c_str();
      glGetUniformIndices(shaderProgram, 1, &nameCST,
         &uniformIdx);
      GLSLParser::GLSLType type = getUniformType(uniformIdx);

      auto foundUnif = uniforms.find(uniformName);
      if(foundUnif!= uniforms.end())
      {
         foundUnif->second.setID(unifId);
      }
      else
      {
         auto empl = uniforms.emplace(uniformName,GLSLParser::UniformObject(uniformName,type,unifId));
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
      boundAttributes[attribName] = true;
      return attributeId->second;
   }

}

GLSLParser::UniformObject Program::getUniform(std::string unifName)
{
   if(!created)
   {
      LOG(ERROR) << "Program" + name + " has not been created. Call .create()";
      return GLSLParser::UniformObject("badObject",GLSLParser::GLSLInvalidType,-1);
   }
   auto unifId = uniforms.find(unifName);
   if(unifId == uniforms.end())
   {
      LOG(WARNING) << "Program " + name + " has no uniform named " + unifName + " (Did you forget to add it to the program?)";
      return GLSLParser::UniformObject("badObject",GLSLParser::GLSLInvalidType,-1);
   }
   else
   {
      boundUniforms[unifName] = true;
      return unifId->second;
   }
}

bool Program::hasUniform(std::string unifName)
{
   if(!created)
   {
      LOG(ERROR) << "Program " + name + " has not been created. Call .create()";
      return false;
   }
   if(uniforms.find(unifName) == uniforms.end() &&
      uniformStructs.find(unifName) == uniformStructs.end() &&
      arrays.find(unifName) == arrays.end() &&
      structArrays.find(unifName) == structArrays.end())
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

int Program::addUniformStruct(std::string name, GL_Structure glStruct)
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
         glStruct.setUniformLocation(*i,getUniform(name + "." +*i).getID());
      }
      uniformStructs[name] = glStruct;

      return 0;
   }
   else
   {
      LOG(ERROR) << "Struct " + name + " Could not find all attributes!";
      return -1;
   }
}

int Program::addUniformArray(std::string name, int len)
{
   bool canAddArray = true;
   std::vector<GLint> locs;
   for(int i = 0; i < len; i++)
   {
      std::string unifName = name + "[" + std::to_string(i) + "]";
      GLint loc = glGetUniformLocation(shaderProgram, unifName.c_str());
   
      if(loc == -1)
      {
         LOG(ERROR) << "Could not find array uniform " << unifName << std::endl;
      }
      canAddArray &= (loc != -1);
      locs.push_back(loc);
   }

   if(!canAddArray || len <= 0)
   {
      LOG(ERROR) << "Could not add array " + name + ", name wrong or length wrong";
      return -1;
   }
   else
   {
      UniformArrayInfo info;
      info.baseName = name;
      info.locations = locs;
      info.isValid = true;
      arrays[name] = info;
      return 0;
   }

}

int Program::addStructArray(std::string name, int len, GL_Structure  template_struct)
{
   if(len > 0)
   {
      bool canAddStruct = true;
      std::vector<std::string> uniformNames = template_struct.getUniformNames();
      int canAddUniform = 0;
      UniformStructArrayInfo info;
      info.baseName = name;
      for(int i = 0; i < len; i++)
      {
         GL_Structure glStruct(template_struct);
         for (std::vector<std::string>::iterator atrb = uniformNames.begin(); atrb != uniformNames.end(); ++atrb)
         {
            std::string unifName = name + "["+std::to_string(i)+"]."+*atrb;
            GLint unifLoc = glGetUniformLocation(shaderProgram,unifName.c_str());
            canAddStruct &= (unifLoc != -1);
            canAddStruct &= (glStruct.setUniformLocation(*atrb,unifLoc) == 0);
         }
         info.structs.push_back(glStruct);
      }
      if(!canAddStruct)
      {
         LOG(ERROR) << "Could not bind struct array";
         return -1;
      }
      else
      {
         info.isValid = true;
         structArrays[name] = info;
         return 0;
      }
   }
   else
   {
      return -1;
   }
}
GL_Structure Program::getUniformStruct(std::string name)
{
   if(uniformStructs.find(name) != uniformStructs.end())
     return uniformStructs[name];
   else
   {
      LOG(ERROR) << "Could not find structure named " << name << ", did you add it to the program?";
      return GL_Structure();
   }
}
const Program::UniformArrayInfo  & Program::getArray(std::string name)
{

  if(arrays.find(name) != arrays.end())
     return arrays[name];
   else
   {

      return emptyUniformArray;
   }
}

const Program::UniformStructArrayInfo &  Program::getStructArray(std::string name)
{
  if(structArrays.find(name) != structArrays.end())
     return structArrays[name];
  else
  {
     return emptyStructUniformArray;
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

GLSLParser::GLSLType Program::getUniformType(GLuint id)
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

   return GLSLParser::GLEnumToGLSLType(type);
}


