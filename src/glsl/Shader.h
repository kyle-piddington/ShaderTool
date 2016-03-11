#ifndef __SHADER_H__
#define __SHADER_H__
#include "ReloadableAsset.h"
#include <glfw/glfw3.h>

/**
 * A shader is a wrapper class for handling the livetime of a shader on a GPU.
 * The shader class performs operations such as shader compalation, creation, and removal.
 * The shader implements ReloadableAsset, and can handle being reloaded if need be. However, it relies 
 * on the program class to recompile it.
 */
class Shader : public ReloadableAsset
{
public:
   /**
    * Construct a shader. The path should either be an absolute path, or relative to
    * the running directory of the program.
    */
   Shader(std::string path, GLenum shaderType);
   /**
    * The desconstructor for shader will not handle removing it from a GPU, Program
    * will manage the lifetime of the shader objects.
    */
   ~Shader();
   
   /**
    * Compile a shader on the GPU
    * @return 0 if OK, -1 otherwise
    */
   int compile();

   /**
    * Mark a shader for reloading. Program will use isCompiled to check and force
    * recompiling the shader, as shaders can't be compiled outside of a program context.
    */
   virtual void reload();
   
   /**
    * Retrieve the path of the shader
    * @return the path given on construction
    */
   virtual std::string getPath();

   /**
    * Check to see if the program has been compiled since any changes
    * This method will return true if the shader fails to compile, as long as it was attempted.
    * @TODO pick a better name for this function
    * @return true if no changes have occured from last compilation.
    */
   bool isCompiled();

   /**
    * Get the ID of the shader on the GPU, or 0 if the shader has not been created
    * @return the ID.
    */
   GLuint getID();

   /**
    * Delete this shader from the GPU
    * @return 0 if the shader was successfully deleted, -1 otherwise.
    */
   int deleteFromGPU();

   const std::string getName() const
   {
      return path;
   }
private:
   std::string path;
   GLuint shaderID;
   GLenum shaderType;
   bool isShaderCompiled;

};
#endif