#include "Material.h"
#include <glm/gtc/type_ptr.hpp>


Material::Material(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shininess):
ambient(amb),
diffuse(diff),
specular(spec),
shininess(shininess)
{

}

void Material::bind(const UniformObject &  ambLoc,
                    const UniformObject &  diffLoc,
                    const UniformObject &  specLoc,
                    const UniformObject &  shininessLoc)
{
   ambLoc.bind(ambient);
   diffLoc.bind(diffuse);
   specLoc.bind(specular);
   shininessLoc.bind(shininess);
}

void Material::bind(const UniformObject & material)
{
   material["ambient"].bind(ambient);
   material["diffuse"].bind(diffuse);
   material["specular"].bind(specular);
   material["shininess"].bind(shininess);

}
