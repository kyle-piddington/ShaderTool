#include "CubemapScene.h"
#include <glm/gtc/type_ptr.hpp>
#include "GlmUtil.h"

CubemapScene::CubemapScene(Context * ctx) :
CameraScene(ctx),
crate("assets/textures/container.jpg")
{
   std::vector<std::string> texPaths;
   texPaths.push_back("assets/textures/skybox/right.jpg");
   texPaths.push_back("assets/textures/skybox/left.jpg");
   texPaths.push_back("assets/textures/skybox/top.jpg");
   texPaths.push_back("assets/textures/skybox/bottom.jpg");
   texPaths.push_back("assets/textures/skybox/back.jpg");
   texPaths.push_back("assets/textures/skybox/front.jpg");
   cubeMap.init(texPaths);
   texProg = createProgram("Texture display program");
   skyboxProg = createProgram("Skybox program");
   reflectProg = createProgram("Reflection program");
   skyboxCube.transform.setScale(glm::vec3(100));
   //reflectCube.transform.setPosition(glm::vec3(2,0,0));
}

void CubemapScene::initPrograms()
{
   texProg->addVertexShader("assets/shaders/tex_vert_layout.vs");
   texProg->addFragmentShader("assets/shaders/tex_frag.fs");

   skyboxProg->addVertexShader("assets/shaders/skybox_vert.vs");
   skyboxProg->addFragmentShader("assets/shaders/skybox_frag.fs");

   reflectProg->addVertexShader("assets/shaders/reflect_vert.vs");
   reflectProg->addFragmentShader("assets/shaders/reflect_frag.fs");

}

void CubemapScene::initialBind()
{
   texProg->addUniform("M");
   texProg->addUniform("V");
   texProg->addUniform("P");
   texProg->addUniform("tex");

   skyboxProg->addUniform("M");
   skyboxProg->addUniform("V");
   skyboxProg->addUniform("P");
   skyboxProg->addUniform("skybox");

   reflectProg->addUniform("M");
   reflectProg->addUniform("V");
   reflectProg->addUniform("P");
   reflectProg->addUniform("N");
   reflectProg->addUniform("skybox");
   reflectProg->addUniform("cameraPos");



   glm::mat4 P;
   texProg->enable();
   P = camera.getPerspectiveMatrix();
   texProg->getUniform("P").bind(P);

   skyboxProg->enable();
   skyboxProg->getUniform("P").bind(P);

   reflectProg->enable();
   reflectProg->getUniform("P").bind(P);


   skyboxProg->disable();
   glEnable(GL_DEPTH_TEST);
   glClearColor(1.0,0.0,1.0,1.0);
}

void CubemapScene::render()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   glDepthFunc(GL_LESS);
   glm::mat4 V;
   V = camera.getViewMatrix();
   texProg->enable();
   texProg->getUniform("M").bind(cube.transform.getMatrix());
   texProg->getUniform("V").bind(V);

   //crate.enable(texProg->getUniform("tex"));
   //cube.render();
   //crate.disable();


   reflectProg->enable();
   //reflectCube.transform.rotate(glm::vec3(M_PI/128.0,M_PI/200.0,0));
   reflectProg->getUniform("M").bind(reflectCube.transform.getMatrix());
   glm::mat3 N = GlmUtil::createNormalMatrix(glm::mat4(1.0),reflectCube.transform.getMatrix());
   reflectProg->getUniform("N").bind(N);
   reflectProg->getUniform("V").bind(V);
   glm::vec3 camPos = camera.getPosition();
   reflectProg->getUniform("cameraPos").bind(camPos);
   cubeMap.enable(reflectProg->getUniform("skybox").getID());
   reflectCube.render();
   


   glm::mat4 skyView = glm::mat4(glm::mat3(V));
   skyboxProg->enable();
   glDepthFunc(GL_LEQUAL);
   skyboxProg->getUniform("M").bind(skyboxCube.transform.getMatrix());
   skyboxProg->getUniform("V").bind(skyView);
   cubeMap.enable(skyboxProg->getUniform("skybox").getID());
   skyboxCube.render();
   //cubeMap.disable();
   skyboxProg->disable();
}