#include "EmptyScene.h"

EmptyScene::EmptyScene() : Scene()
{

}
EmptyScene::~EmptyScene()
{
   
}
void EmptyScene::initPrograms()
{  


}
void EmptyScene::initialBind()
{
   glClearColor(0.75f, 0.52f, 0.3f, 1.0f);
   glEnable(GL_DEPTH_TEST);
}
void EmptyScene::render()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void EmptyScene::update()
{

}
void EmptyScene::cleanup()
{

}