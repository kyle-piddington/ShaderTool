#ifndef __TOOLSCENE_PROGRAM_MGR_H__
#define __TOOLSCENE_PROGRAM_MGR_H__
#include "Program.h"
#include "UniformObjectController.h"
#include <set>
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
    * Get controllers to a set of exposed uniform objects
    */
   const std::vector<std::shared_ptr<UniformObjectController>> & getExposedUniformControllers() const;
   /**
    * Reload the active program (If possible).
    * return true if the reload was successful.
    */
   bool reload();

   void bindDefaultVariables(glm::mat4 V, glm::mat4 P, float iGlobalTime);

   std::shared_ptr<UniformObjectController> getModelUniformController();

   void updateModelMatrix(glm::mat4 M);

private:
   std::set<std::string> reservedNames;
   std::unordered_map<std::string, std::shared_ptr<UniformObjectController>> internalControllers;
   std::vector<std::shared_ptr<UniformObjectController>> exposedControlers;

   /**
    * Refresh accessable controlleres
    */
   void refreshControllers();
   
   /**
    * Assign a uniform object to a controller
    * @param obj the object to assign
    */
   void assignController(std::shared_ptr<UniformObject> obj,  std::vector<std::shared_ptr<UniformObjectController>>  & oldControllers);
   /**
    * Called on init, set up the reserved names used by the program manager.
    */
   void populateReservedNames();

   /**
    * Bind an old controller to an updated uniform object if the name and type matches.
    * Otherwise, return nullptr if no match.
    */
   std::shared_ptr<UniformObjectController> bindOldController(
         std::shared_ptr<UniformObject> obj, 
         std::vector<std::shared_ptr<UniformObjectController>>  & oldControllers);
   
   std::shared_ptr<Program> activeProgram;

   glm::mat4 currM;
   glm::mat4 currV;
   glm::mat4 currP;
   glm::mat4 currN;
   float iCurrGlobalTime;


};
#endif