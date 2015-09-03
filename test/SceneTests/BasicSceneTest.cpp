#include <gtest/gtest.h>
#include "Scene.h"
#include "EmptyScene.h"
#include "ReloadLocator.h"
class TestScene1 : public EmptyScene
{
   virtual void initPrograms()
   {
      Program * prog = createProgram("Test program");
      prog->addVertexShader("test/testAssets/basicVert.vs");
      prog->addFragmentShader("test/testAssets/basicFrag.fs");

   }
};
TEST(BasicSceneTests, testSceneCreation)
{
   Scene * scene = new TestScene1();
   //Scenes can run with no programs.
   EXPECT_EQ(true, scene->canRenderScene());
   scene->initPrograms();
   //Scenes must compile programs before running, if added
   EXPECT_EQ(false, scene->canRenderScene());
   scene->compilePrograms();
   //Scenes can run after a successful first compile.
   EXPECT_EQ(true, scene->canRenderScene());

}

TEST(BasicSceneTests, testSceneReloadFlag)
{
   Scene * scene = new TestScene1();
   scene->initPrograms();
   scene->compilePrograms();
   EXPECT_EQ(true, scene->canRenderScene());
   EXPECT_EQ(false, scene->shouldReloadScene());

   FileSystem::ReloadLocator::getService()->processEvents();
   EXPECT_EQ(true, scene->shouldReloadScene());
   scene->compilePrograms();
   EXPECT_EQ(false, scene->shouldReloadScene());

}

class TestScene2 : public EmptyScene
{
   virtual void initPrograms()
   {
      Program * prog = createProgram("Test Error program");
      prog->addVertexShader("test/testAssets/badVert.vs");
      prog->addFragmentShader("test/testAssets/basicFrag.fs");

   }
};
TEST(BasicSceneTests, badProgramTest)
{
   Scene * scene = new TestScene2();
   scene->initPrograms();
   scene->compilePrograms();
   EXPECT_EQ(false, scene->canRenderScene());
}

