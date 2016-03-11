#ifndef __TOOLSCENE_PROGRAM_MGR_H__
#define __TOOLSCENE_PROGRAM_MGR_H__
#include "Program.h"
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
   std::string getVertexName() const;
   /**
    * Get the name of the fragment shader
    * @return the fragment shader name.
    */
   std::string getFragmentName() const;

   /**
    * Get the active program
    */
   const std::shared_ptr<Program> getActiveProgram() const;

   /**
    * Reload the active program (If possible).
    * return true if the reload was successful.
    */
   bool reload();

   void bindDefaultVariables(glm::mat4 M, glm::mat4 V, glm::mat4 P, float iGlobalTime);


private:

   std::shared_ptr<Program> activeProgram;
   glm::mat4 currM;
   glm::mat4 currV;
   glm::mat4 currP;
   glm::mat4 currN;
   float iCurrGlobalTime;


};
#endif