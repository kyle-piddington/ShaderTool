#ifndef __GLM_UTILS_H__
#define __GLM_UTILS_H__
namespace GlmUtil
{
   glm::mat3 createNormalMatrix(const glm::mat4  view, const glm::mat4 model)
   {
      return glm::mat3(glm::transpose(glm::inverse(view * model)));
   }
}
#endif