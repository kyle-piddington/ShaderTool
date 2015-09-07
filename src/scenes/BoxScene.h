#include "VertexArrayObject.h"
#include "GL_Structure.h"
#include <glm/glm.hpp>
#include "Scene.h"
#include "Camera.h"
#include "Spotlight.h"
#include "Light.h"
#include "VertexBuffer.h"
#include "Light.h"
#include "TexturedMaterial.h"
#include "DirectionalLight.h"
#include "Material.h"


class BoxScene : public Scene
{
   public:
      BoxScene(Context * ctx);
      virtual ~BoxScene();
      virtual void initPrograms();
      virtual void initialBind();
      virtual void render();
      virtual void update();
      virtual void cleanup();
   private:
      Camera * camera;

      Program * phongProg;
      Program * lampProg;
      GL_Structure spotlightStruct = Spotlight::getStruct();
      GL_Structure lampStruct = Light::getStruct();
      GL_Structure dirLightStruct = DirectionalLight::getStruct();
      GL_Structure matStruct = Material::getStruct();

      DirectionalLight dirLight;
      TexturedMaterial cubeMaterial;
      Light lamp;
      VertexArrayObject boxVao, lightVao;
      Spotlight spotlight;
      VertexBuffer vbo;
  

};