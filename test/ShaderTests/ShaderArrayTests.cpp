#include <gtest/gtest.h>
#include <Program.h>
TEST(ArrayShaderTests, checkProgramsOK)
{
    Program program("Test1");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/arrayFrag.fs"));
   EXPECT_EQ(0,program.create());
}
TEST(ArrayShaderTests, testUniformArray)
{
   Program program("Test2");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/arrayFrag.fs"));
   EXPECT_EQ(0,program.create());

   EXPECT_EQ(0,program.addUniformArray("intArr",10));

}

TEST(ArrayShaderTests, testStructArray)
{
   Program program("Test3");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/arrayFrag.fs"));
   EXPECT_EQ(0,program.create());

   GL_Structure testStruct;
   testStruct.addAttribute("testVec1");
   testStruct.addAttribute("testVec2");
   testStruct.addAttribute("testVec3");
   EXPECT_EQ(0,program.addStructArray("structArr",10,testStruct));
}

TEST(ArrayShaderTests, testLenBounds)
{
   Program program("Test4");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/arrayFrag.fs"));
   EXPECT_EQ(0,program.create());

   EXPECT_EQ(-1,program.addUniformArray("intArr",11));
   EXPECT_EQ(-1,program.addUniformArray("intArr",0));

}

TEST(ArrayShaderTests, testLenBoundsStruct)
{
   Program program("Test5");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/arrayFrag.fs"));
   EXPECT_EQ(0,program.create());

   GL_Structure testStruct;
   testStruct.addAttribute("testVec1");
   testStruct.addAttribute("testVec2");
   testStruct.addAttribute("testVec3");
   EXPECT_EQ(-1,program.addStructArray("structArr",11,testStruct));
   EXPECT_EQ(-1,program.addStructArray("structArr",0,testStruct));

}

TEST(ArrayShaderTests, testBadStruct)
{
   Program program("Test6");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/arrayFrag.fs"));
   EXPECT_EQ(0,program.create());

   GL_Structure testStruct;
   testStruct.addAttribute("testVec1");
   testStruct.addAttribute("testVec2");
   testStruct.addAttribute("testVec4");
   EXPECT_EQ(-1,program.addStructArray("structArr",10,testStruct));

}
TEST(ArrayShaderTests, testArrAccess)
{
   Program program("Test7");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/arrayFrag.fs"));
   EXPECT_EQ(0,program.create());

   EXPECT_EQ(0,program.addUniformArray("intArr",10));
   Program::UniformArrayInfo info = program.getArray("intArr");
   for(int i = 0; i < 10; i++)
   {
      EXPECT_EQ(program.hasUniform("intArr[" + std::to_string(i) + "]"), info[i]);
   }
}
TEST(ArrayShaderTests, testStructAccess)
{
   Program program("Test8");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/arrayFrag.fs"));
   EXPECT_EQ(0,program.create());
   GL_Structure testStruct;
   testStruct.addAttribute("testVec1");
   testStruct.addAttribute("testVec2");
   testStruct.addAttribute("testVec3");

   EXPECT_EQ(0,program.addStructArray("structArr",10,testStruct));
   Program::UniformStructArrayInfo info = program.getStructArray("structArr");
   std::vector<std::string> attribNames = testStruct.getUniformNames();
   for(int i = 0; i < 10; i++)
   {
      GL_Structure checkStruct = info[i];
      for (std::vector<std::string>::iterator atrb = attribNames.begin(); atrb != attribNames.end(); ++atrb)
      {
        EXPECT_EQ(program.hasUniform("structArr[" + std::to_string(i) + "]."+*atrb), info[i][*atrb]);
      }
   }
}