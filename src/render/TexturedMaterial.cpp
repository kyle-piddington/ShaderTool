#include "TexturedMaterial.h"
#include <glm/gtc/type_ptr.hpp>

TexturedMaterial::TexturedMaterial(std::string diffTexture, std::string specTexture, std::string emissionTexture, float shininess):
diffuseMap(diffTexture),
specularMap(specTexture),
emissionMap(emissionTexture),
shininess(shininess)
{

}

void TexturedMaterial::bind(GLint diffLoc, GLint specLoc, GLint emissionLoc, GLint shininessLoc)
{
   diffuseMap.enable(diffLoc);
   specularMap.enable(specLoc);
   emissionMap.enable(emissionLoc);
   glUniform1f(shininessLoc,shininess);
}
void TexturedMaterial::unbind()
{
   diffuseMap.disable();
   specularMap.disable();
   emissionMap.disable();
}
