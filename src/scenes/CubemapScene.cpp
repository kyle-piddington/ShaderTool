#include "CubemapScene.h"
#include <glm/gtc/type_ptr.hpp>

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
   skyboxCube.transform.setScale(glm::vec3(100));
}

void CubemapScene::initPrograms()
{
   texProg->addVertexShader("assets/shaders/tex_vert_layout.vs");
   texProg->addFragmentShader("assets/shaders/tex_frag.fs");
  
   skyboxProg->addVertexShader("assets/shaders/skybox_vert.vs");
   skyboxProg->addFragmentShader("assets/shaders/skybox_frag.fs");
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


   glm::mat4 P;
   texProg->enable();
   P = camera.getPerspectiveMatrix();
   glUniformMatrix4fv(texProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));
   
   skyboxProg->enable();
   glUniformMatrix4fv(skyboxProg->getUniform("P"),1,GL_FALSE,glm::value_ptr(P));
   
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
   glUniformMatrix4fv(texProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(cube.transform.getMatrix()));
   glUniformMatrix4fv(texProg->getUniform("V"),1,GL_FALSE,glm::value_ptr(V));
  
   crate.enable(texProg->getUniform("tex"));
   cube.render();
   crate.disable();

   glm::mat4 skyView = glm::mat4(glm::mat3(V));
   skyboxProg->enable();
   glDepthFunc(GL_LEQUAL);
   glUniformMatrix4fv(skyboxProg->getUniform("M"),1,GL_FALSE,glm::value_ptr(skyboxCube.transform.getMatrix()));
   glUniformMatrix4fv(skyboxProg->getUniform("V"),1,GL_FALSE,glm::value_ptr(skyView));
   cubeMap.enable(skyboxProg->getUniform("skybox"));
   skyboxCube.render();
   cubeMap.disable();
   skyboxProg->disable();
}