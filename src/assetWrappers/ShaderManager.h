#ifndef __SHADER_MANAGER_H__
#define __SHADER_MANAGER_H__
#include "Shader.h"
#include <unordered_map>
class ShaderManager
{
public:
   static std::shared_ptr<Shader> getShader(std::string shader, GLenum shaderType);
   static void cleanup();
private:
   static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};
#endif