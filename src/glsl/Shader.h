#ifndef __SHADER_H__
#define __SHADER_H__
#include "ReloadableAsset.h"
#include <glfw/glfw3.h>
class Shader : public ReloadableAsset
{
public:
   Shader(std::string path, GLenum shaderType);
   ~Shader();
   int compile();
   virtual void reload();
   virtual std::string getPath();
   bool isCompiled();
   GLuint getID();
   int deleteFromGPU();
private:
   std::string path;
   GLuint shaderID;
   GLenum shaderType;
   bool isShaderCompiled;

};
#endif