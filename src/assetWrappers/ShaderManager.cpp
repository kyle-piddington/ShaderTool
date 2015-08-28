#include "ShaderManager.h"

std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderManager::shaders;

 std::shared_ptr<Shader> ShaderManager::getShader(std::string shaderName, GLenum shaderType)
{
   std::shared_ptr<Shader> ret = nullptr;
   auto preloadedShader = shaders.find(shaderName);
   if(preloadedShader == shaders.end())
   {
      ret = std::shared_ptr<Shader>(new Shader(shaderName, shaderType));
      shaders[shaderName] = ret;
   }
   else
   {
      ret = preloadedShader->second;
   }
   return ret;
}

void ShaderManager::cleanup()
{
   for(auto iter = shaders.begin(); iter != shaders.end(); iter++)
   {
      iter->second->deleteFromGPU();
   }
}