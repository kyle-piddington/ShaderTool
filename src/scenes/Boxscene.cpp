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
#include "Mouse.h"
#include "Keyboard.h"
#include <glm/gtc/type_ptr.hpp>
#define NUM_POINT_LIGHTS 4
#define DEG2RAD(angleDegrees) (angleDegrees * M_PI / 180.0)


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

};

//Helper functions
glm::mat3 createNormalMatrix(const glm::mat4 & view, const glm::mat4 & model)
{
   return glm::mat3(glm::transpose(glm::inverse(view * model)));
}

void handleCameraInput(Camera & camera, Context * ctx)
{
   static float pitch = 0;
   static float yaw = 0;

   const float Cam_Speed = 1.0/30.0;
   const float Cam_Rot_Speed = M_PI;
   glm::vec3 translate(0.0);
   glm::vec3 rotate(0.0);
   if(Keyboard::isKeyDown(GLFW_KEY_W))
   {
      translate += camera.transform.forward() * Cam_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_S))
   {
      translate -= camera.transform.forward() * Cam_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_A))
   {
      translate-= camera.transform.right() * Cam_Speed;
   }
   if(Keyboard::isKeyDown(GLFW_KEY_D))
   {
      translate+= camera.transform.right() * Cam_Speed;
   }
   if(Mouse::pressed(GLFW_MOUSE_BUTTON_LEFT))
   {
      rotate.x = (Mouse::getLastY() - Mouse::getY())/ctx->getWindowHeight()/2.0 * Cam_Rot_Speed;
      rotate.y = (Mouse::getLastX() - Mouse::getX())/ctx->getWindowWidth()/2.0 * Cam_Rot_Speed;
      pitch += rotate.x;
      yaw += rotate.y;
      rotate.z = 0;
   }
   camera.translate(translate);
   camera.setRotation(glm::vec3(pitch,yaw,0));
}

//Const scene data

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
  };

glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
glm::vec3 pointLightColors[] = {
    glm::vec3(1.0f, 0.6f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0, 0.0),
    glm::vec3(0.2f, 0.2f, 1.0f)
  };



BoxScene::BoxScene(Context * ctx) : Scene(ctx),
   cubeMaterial(
               "assets/textures/container2.png",
               "assets/textures/container2_specular.png",
               "assets/textures/solid_black.png",
               32.0f),
   lamp(
      glm::vec3(0.2),
      glm::vec3(0.5),
      glm::vec3(1.0),
      50.0f),
  
   dirLight(glm::vec3(0.2f, -1.0f, -0.3f),
                             glm::vec3( 0.3f, 0.24f, 0.14f),
                             glm::vec3(0.7f, 0.42f, 0.26f),
                             glm::vec3( 0.5f, 0.5f, 0.5f)),

   spotlight(glm::vec3(0.0),
                       glm::vec3(2.9),
                       glm::vec3(2.9),
                       DEG2RAD(12.5f),
                       DEG2RAD(17.5f),
                       50.0f)
{
   camera = new Camera(ctx->getWindowWidth(), ctx->getWindowHeight());
   GLfloat vertices[] = {
    // Positions           // Normals           // Texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
  };
  VertexBuffer vbo;
  vbo.setData(vertices, 36*8);

  boxVao.addAttribute(phongProg->getAttribute("position"),vbo,8*sizeof(GLfloat));
  boxVao.addAttribute(phongProg->getAttribute("normal"),vbo,8*sizeof(GLfloat),3*sizeof(GLfloat));
  boxVao.addAttribute(phongProg->getAttribute("vertTexCoords"),vbo,8*sizeof(GLfloat),6*sizeof(GLfloat),2);
  lightVao.addAttribute(this->phongProg->getAttribute("position"),vbo, 8*sizeof(GLfloat));

  phongProg = createProgram("Phong Shade Program");
  lampProg = createProgram("Lamp display program");


}

BoxScene::~BoxScene()
{

}
void BoxScene::initPrograms()
{
   phongProg->addVertexShader("assets/shaders/phong_vert_textured.vs");
   phongProg->addFragmentShader("assets/shaders/phong_frag_textured.fs");

   lampProg->addVertexShader("assets/shaders/debug_vert.vs");
   lampProg->addFragmentShader("assets/shaders/debug_frag.fs");

}
void BoxScene::initialBind()
{

   //Program setup
   phongProg->addAttribute("position");
   phongProg->addAttribute("normal");
   phongProg->addAttribute("vertTexCoords");

   phongProg->addUniform("M");
   phongProg->addUniform("V");
   phongProg->addUniform("P");
   phongProg->addUniform("N");

   phongProg->addStructArray("pointLights",NUM_POINT_LIGHTS,lampStruct);
   phongProg->addUniformStruct("material",matStruct);
   phongProg->addUniformStruct("dirLight",dirLightStruct);
   phongProg->addUniformStruct("flashLight",spotlightStruct);

   lampProg->addAttribute("position");
   lampProg->addUniform("M");
   lampProg->addUniform("V");
   lampProg->addUniform("P");
   lampProg->addUniform("debugColor");

   //Scene setup
   glEnable(GL_DEPTH_TEST);
   camera->setPosition(glm::vec3(0,0,5));
 
   phongProg->enable();
   dirLight.bind(dirLightStruct.get("direction"),
                 dirLightStruct.get("ambient"),
                 dirLightStruct.get("diffuse"),
                 dirLightStruct.get("specular"));




   glClearColor(0.75f, 0.52f, 0.3f, 1.0f);
}
void BoxScene::render()
{

   glm::mat4 P,M,V;
   glm::mat3 NORM;
   //Perspective
   if(Keyboard::isKeyToggled(GLFW_KEY_O))
   {
      P = camera->getOrthographicMatrix();
   }
   else
   {
      P = camera->getPerspectiveMatrix();
   }
   phongProg->enable();
   //View
   V = camera->getViewMatrix();
   //Phong lighting section
   phongProg->enable();

   //Camera
   glUniformMatrix4fv(phongProg->getUniform("V"), 1, GL_FALSE, glm::value_ptr(V));
   glUniformMatrix4fv(phongProg->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));

   //Lighting
   Program::UniformStructArrayInfo lampArr = phongProg->getStructArray("pointLights");
      for(int i = 0; i < NUM_POINT_LIGHTS; i++)
      {
        Light tempLamp(lamp);
        tempLamp.transform.setPosition(pointLightPositions[i]);
        tempLamp.ambient = pointLightColors[i];
        tempLamp.diffuse = pointLightColors[i];
        tempLamp.specular = pointLightColors[i];

        tempLamp.bind(
           lampArr[i].get("position"),
           lampArr[i].get("ambient"),
           lampArr[i].get("diffuse"),
           lampArr[i].get("specular"),
           lampArr[i].get("constant"),
           lampArr[i].get("linear"),
           lampArr[i].get("quadratic"));
      }



   //Spotlight lighting
   spotlight.transform().copy(camera->transform);
   spotlight.bind(
        spotlightStruct.get("position"),
        spotlightStruct.get("direction"),
        spotlightStruct.get("ambient"),
        spotlightStruct.get("diffuse"),
        spotlightStruct.get("specular"),
        spotlightStruct.get("cutOff"),
        spotlightStruct.get("outerCutOff"),
        spotlightStruct.get("constant"),
        spotlightStruct.get("linear"),
        spotlightStruct.get("quadratic"));
   //Texturing
   cubeMaterial.bind(
         matStruct.get("diffuse"),
         matStruct.get("specular"),
         matStruct.get("emission"),
         matStruct.get("shininess")

   );
   //Draw 10 cubes
   Transform cubeTransform;
   boxVao.bind();

   for(int i = 0; i < 10; i++)
      {
        cubeTransform.setPosition(cubePositions[i]);
        cubeTransform.setRotation(glm::vec3(M_PI/12 * i, M_PI/6 * i, 0.0));
        M = cubeTransform.getMatrix();
        NORM = createNormalMatrix(V, M);
        glUniformMatrix3fv(phongProg->getUniform("N"), 1, GL_FALSE, glm::value_ptr(NORM));
        glUniformMatrix4fv(phongProg->getUniform("M"), 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES,0,36);
      }



   //Draw  lamps
   lampProg->enable();
   lightVao.bind();
   glUniformMatrix4fv(lampProg->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P));
   glUniformMatrix4fv(lampProg->getUniform("V"), 1, GL_FALSE, glm::value_ptr(V));
   for(int i = 0; i < NUM_POINT_LIGHTS; i++)
   {
        Transform mTransform;
        mTransform.setPosition(pointLightPositions[i]);
        mTransform.setScale(glm::vec3(0.2));
        M = mTransform.getMatrix();
        glUniform3fv(lampProg->getUniform("debugColor"),1,glm::value_ptr(pointLightColors[i]));
        glUniformMatrix4fv(lampProg->getUniform("M"), 1, GL_FALSE, glm::value_ptr(M));
        glDrawArrays(GL_TRIANGLES,0,36);
   }


}
void BoxScene::update()
{
   handleCameraInput(*camera,getContext());
}
void BoxScene::cleanup()
{
   delete camera;
}
