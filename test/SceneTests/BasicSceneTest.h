#include <gtest/gtest.h>
#include "Scene.h"
#include "ResourceLocator.h"
TEST(BasicSceneTests, testSceneCreation)
{
   Scene scene;
   EXPECT_EQ(false, scene->canRenderScene())
   Program * prog = scene.create_program("Test program");
   prog->addVertexShader("testAssets/basicVert.vs");
   prog->addFragmentShader("testAssets/basicFrag.fs");
   EXPECT_EQ(false, scene->canRenderScene());
   scene->initPrograms();
   EXPECT_EQ(true, scene->canRenderScene());


}

TEST(BasicSceneTests, testSceneReloadFlag)
{
   Scene scene;
   Program * prog = scene.create_program("Test program");
   prog->addVertexShader("testAssets/basicVert.vs");
   prog->addFragmentShader("testAssets/basicFrag.fs");
   scene->initPrograms();
   EXPECT_EQ(true, scene->canRenderScene());
   EXPECT_EQ(false, scene->shouldReloadScene());

   FileSystem::ReloadLocator::getService()->processEvents();
   EXPECT_EQ(true, scene->shouldReloadScene());
   scene->initPrograms();
   EXPECT_EQ(false, scene->shouldReloadScene());

}

