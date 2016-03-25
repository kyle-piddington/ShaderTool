#include <GL/glew.h>

#include <UniformExtractor.h>
#include <ArrayUniformObject.h>
#include <StructUniformObject.h>
#include <GLSLType.h>

#include "GL_Logger.h"
UniformExtractor::UniformExtractor()
{

}
UniformExtractor::~UniformExtractor()
{

}

std::vector < std::shared_ptr < UniformObject > > UniformExtractor::extract(GLuint pid)
{
  std::vector<std::shared_ptr < UniformObject > > uniforms;
  /**
   * Get the number of uniforms
   */
  GLint numUniforms;
  glGetProgramiv(pid, GL_ACTIVE_UNIFORMS, &numUniforms);
  GL_Logger::LogError("Could not get the number of uniforms.");
  std::vector<GLuint> indicies;
  for(unsigned int i = 0; i < numUniforms; i++)
  {
    indicies.push_back(i);
  }

  //Generate uniofrm arrays
  std::vector<int> blockInds(numUniforms);
  std::vector<int> nameLens(numUniforms);
  std::vector<GLint> types(numUniforms);

  glGetActiveUniformsiv(pid, numUniforms, &(indicies[0]), GL_UNIFORM_NAME_LENGTH, &(nameLens[0]));
  GL_Logger::LogError("Could not get the length of uniform names.");
  glGetActiveUniformsiv(pid, numUniforms, &(indicies[0]), GL_UNIFORM_TYPE, &(types[0]));
  GL_Logger::LogError("Could not get the type of uniforms.");
  /**
   * Get the uniforms that aren't in a block.
   */
  for(unsigned int unif = 0; unif < numUniforms; ++unif)
  {
    //Skip any uniforms that are in a block.
    GLint blockIdx = blockInds[unif];

    GLint nameLength = nameLens[unif];
    GLint type = types[unif];
   


    //Get name
    std::vector<char> nameData(nameLength);
    glGetActiveUniformName(pid, unif, nameLength, NULL, &(nameData[0]));
    GL_Logger::LogError("Could not get the uniform name for a uniform..");
    std::string name(nameData.begin(),nameData.end()-1);
    GLint unifId = glGetUniformLocation(pid, name.c_str());
    GL_Logger::LogError("Could not get the location for a uniform.");
    
    /**
     * Create or modify the struct array.
     */
    uniforms.push_back(std::make_shared<UniformObject>(name,GLSLType::GLEnumToGLSLType(type),unifId));
  }
  return uniforms;
}
