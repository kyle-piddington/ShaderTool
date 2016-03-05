#include "DirectionalLight.h"
#include <glm/gtc/type_ptr.hpp>
DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 amb, glm::vec3 diffuse, glm::vec3 specular):
direction(direction),
ambient(amb),
diffuse(diffuse),
specular(specular)
{

}


void DirectionalLight::bind(const UniformObject & dirLoc,
                            const UniformObject & ambLoc,
                            const UniformObject & diffLoc,
                            const UniformObject & specLoc)
{
   dirLoc.bind(direction);
   ambLoc.bind(ambient);
   diffLoc.bind(diffuse);
   specLoc.bind(specular);
}

void DirectionalLight::bind(const UniformObject & dirLight)
{
   dirLight["direction"].bind(direction);
   dirLight["ambient"].bind(ambient);
   dirLight["diffuse"].bind(diffuse);
   dirLight["specualr"].bind(specular);
}
