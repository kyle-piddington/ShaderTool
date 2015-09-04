#ifndef __SHADER_MANAGER_H__
#define __SHADER_MANAGER_H__
#include "Shader.h"
#include <unordered_map>
/**
 * ShaderManager manages storing, and loading shaders. Every shader is only loaded once, allowing 
 * programs to reuse shaders in different programs, without compiling/storing them twice.
 */
class ShaderManager
{
public:
   /**
    * Retrive a shader by name, and type.
    * This method is mainly used by program.cpp, during the retrival of shaders when adding them.
    * @param	shader  The name of the shader (Ususally the relative or absolute path).
    * @param 	shaderType	the type of the shader. If no shader can be found in the map, the type will be used to create one.
    */
   static std::shared_ptr<Shader> getShader(std::string shader, GLenum shaderType);
   /**
    * Delete shaders from the GPU. This step allows for memory management of all shaders at once.
    * @TODO actually use this.
    */
   static void cleanup();
private:
   static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};
#endif