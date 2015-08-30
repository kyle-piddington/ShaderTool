#include <gtest/gtest.h>
#include <Program.h>
#include "ReloadLocator.h"
TEST(BasicShaderTests,testBasicCreation)
{
   Program program("Test1");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/basicFrag.fs"));
   EXPECT_EQ(0,program.create());
}

TEST(BasicShaderTests,testMissingFile)
{
   Program program("Test2");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(-1,program.addFragmentShader("test/testAssets/notExist.fs"));
   //EXPECT_EQ(0,create());
}
TEST(BasicShaderTests,testNotEnoughStages)
{
   Program program("Test3");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(-1,program.create());
   Program program2("Test3_1");
   EXPECT_EQ(0,program2.addFragmentShader("test/testAssets/basicFrag.fs"));
   EXPECT_EQ(-1,program2.create());
}
TEST(BasicShaderTests,testAddAttribute)
{
   Program program("Test4");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/basicFrag.fs"));
   EXPECT_EQ(0,program.create());
   EXPECT_EQ(0,program.addAttribute("position"));
}

TEST(BasicShaderTests,testAttribNotFound)
{
   Program program("Test5");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/basicFrag.fs"));
   EXPECT_EQ(0,program.create());
   EXPECT_EQ(-1,program.addAttribute("notFound"));
}

TEST(BasicShaderTests,testAddUniform)
{
   Program program("Test6");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/basicFrag.fs"));
   EXPECT_EQ(0,program.create());
   EXPECT_EQ(0,program.addUniform("debugColor"));
}


TEST(BasicShaderTests,testAddUniformNotFound)
{
   Program program("Test7");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/basicFrag.fs"));
   EXPECT_EQ(0,program.create());
   EXPECT_EQ(-1,program.addUniform("notFound"));
}

TEST(BasicShaderTests, queryAttribLocation)
{
   Program program("Test8");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/basicFrag.fs"));
   EXPECT_EQ(0,program.create());
   EXPECT_EQ(-1, program.getAttribute("position"));
   EXPECT_EQ(0,program.addAttribute("position"));
   EXPECT_EQ(0, program.getAttribute("position"));
}

TEST(BasicShaderTests,queryUniformLocation)
{
   Program program("Test9");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/basicFrag.fs"));
   EXPECT_EQ(0,program.create());
   EXPECT_EQ(-1,program.getUniform("debugColor"));
   EXPECT_EQ(0,program.addUniform("debugColor"));
   EXPECT_NE(-1,program.getUniform("debugColor"));
}


TEST(BasicShaderTests,checkIfShouldCompile)
{
   Program program("Test9");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/basicFrag.fs"));
   EXPECT_EQ(true, program.shouldProgramRecompile());
   EXPECT_EQ(0,program.create());
   EXPECT_EQ(false, program.shouldProgramRecompile());
}

TEST(BasicShaderTests,checkIfReloaded)
{
   Program program("Test9");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/basicFrag.fs"));
   EXPECT_EQ(true, program.shouldProgramRecompile());
   EXPECT_EQ(0,program.create());
   EXPECT_EQ(false, program.shouldProgramRecompile());
   //Flag programs as in need of recompiling.
   FileSystem::ReloadLocator::getService()->processEvents();
   EXPECT_EQ(true, program.shouldProgramRecompile());
   
}



