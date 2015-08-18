#ifndef __TEXTURED_MATERIAL_H__
#define __TEXTURED_MATERIAL_H__
#include <glm/glm.hpp>
#include "Texture2D.h"
struct TexturedMaterial
{
   TexturedMaterial(std::string diffTexture, std::string specTexture, std::string emissionMap, float shininess);
   
   void bind(GLint diffSampler, GLint specSampler, GLint emissionSampler, GLint shininessLoc);
   void unbind();
   float shininess;
private:
   Texture2D diffuseMap;
   Texture2D specularMap;
   Texture2D emissionMap;

};
#endif