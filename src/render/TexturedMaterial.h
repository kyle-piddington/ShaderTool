#ifndef __TEXTURED_MATERIAL_H__
#define __TEXTURED_MATERIAL_H__
#include <glm/glm.hpp>
#include "Texture2D.h"
#include "GL_Structure.h"
struct TexturedMaterial
{
   TexturedMaterial(std::string diffTexture, std::string specTexture, std::string emissionMap, float shininess);
   
   void bind(GLint diffSampler, GLint specSampler, GLint emissionSampler, GLint shininessLoc);
   void bind(const GL_Structure & glStruct);
   
   void unbind();
   float shininess;

   static  GL_Structure getStruct();
private:
   Texture2D diffuseMap;
   Texture2D specularMap;
   Texture2D emissionMap;

};
#endif