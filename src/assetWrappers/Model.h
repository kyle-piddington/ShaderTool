#ifndef __MODEL_H__
#define __MODEL_H__
#include <vector>
#include "Mesh.h"
#include "Transform.h"
#include <tiny_obj_loader.h>
/**
 * An Assimp renderable model
 */
class Model
{
public:
   Model(std::string path);
   void render(Program & prog);
   std::string getName()
   {
      return name;
   }

private:
   std::vector< std::shared_ptr<Mesh> > meshes;
   std::string name;
   void loadModel(std::string path);
   std::shared_ptr<Mesh> processMesh(tinyobj::mesh_t & mesh);
};

#endif