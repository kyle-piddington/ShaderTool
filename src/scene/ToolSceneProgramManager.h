#ifndef __TOOLSCENE_PROGRAM_MGR_H__
#define __TOOLSCENE_PROGRAM_MGR_H__
#include "Program.h"
#include "GLSLParser.h"
class ToolSceneProgramManager
{

public:
   ToolSceneProgramManager();

   /**
    * Set the program to a new program
    * @param  program the new program
    * @return true if successful
    */
   bool setProgram(Program * program);
   /**
    * Get the name of the vertex shader
    * @return the shader name
    */
   std::string getVertexName();
   /**
    * Get the name of the fragment shader
    * @return the fragment shader name.
    */
   std::string getFragmentName();

   /**
    * Get the active program
    */
   const std::shared_ptr<Program> getActiveProgram();

   /**
    * Reload the active program (If possible).
    * return true if the reload was successful.
    */
   bool reload();

   /**
    * Get a list of the current uniform objects in the
    * active program.
    */
   const std::vector<GLSLParser::UniformObject>
       & getUniformObjects();

private:

   std::shared_ptr<Program> activeProgram;

};
#endif