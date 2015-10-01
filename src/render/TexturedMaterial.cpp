#include "TexturedMaterial.h"
#include <glm/gtc/type_ptr.hpp>

TexturedMaterial::TexturedMaterial(std::string diffTexture, float shininess, std::string specTexture, std::string emissionTexture):
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

void TexturedMaterial::bind(const GL_Structure & matStruct)
{
   bind(matStruct["diffuse"],
        matStruct["specular"],
        matStruct["emission"],
        matStruct["shininess"]);
}

GL_Structure TexturedMaterial::getStruct()
{
   GL_Structure matStruct;
   matStruct.addAttribute("diffuse");
   matStruct.addAttribute("specular");
   matStruct.addAttribute("emission");
   matStruct.addAttribute("shininess");
   return matStruct;
}
void TexturedMaterial::unbind()
{
   diffuseMap.disable();
   specularMap.disable();
   emissionMap.disable();
}
