#include <gtest/gtest.h>
#include <Program.h>
#include <GL_Structure.h>

TEST(StructShaderTests, checkProgramsOK)
{
    Program program("Test1");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/structFrag.fs"));
   EXPECT_EQ(0,program.create());
}

TEST(StructShaderTests, checkStructBoundOK)
{
   Program program("Test2");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/structFrag.fs"));
   EXPECT_EQ(0,program.create());

   GL_Structure testStruct;
   testStruct.addAttribute("testVec1");
   testStruct.addAttribute("testVec2");
   testStruct.addAttribute("testVec3");
   EXPECT_EQ(0,program.addUniformStruct("test",testStruct));
   EXPECT_EQ(program.getUniform("test.testVec1"),testStruct["testVec1"]);
   EXPECT_EQ(program.getUniform("test.testVec2"),testStruct["testVec2"]);
   EXPECT_EQ(program.getUniform("test.testVec3"),testStruct["testVec3"]);
}
TEST(StructShaderTests, testStructCopy)
{
   Program program("Test2");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/structFrag.fs"));
   EXPECT_EQ(0,program.create());

   GL_Structure testStruct;
   testStruct.addAttribute("testVec1");
   testStruct.addAttribute("testVec2");
   testStruct.addAttribute("testVec3");
   

   EXPECT_EQ(0,program.addUniformStruct("test",testStruct));
   GL_Structure testStruct2(testStruct);
   
   //Copy the structure, check to see bound varaibles persist
   EXPECT_EQ(testStruct2.get("testVec1"), testStruct2.get("testVec1"));

   program.addUniformStruct("testStruct2", testStruct2);
   EXPECT_EQ(program.getUniform("testStruct2.testVec1"),testStruct2.get("testVec1"));
   EXPECT_EQ(program.getUniform("testStruct2.testVec2"),testStruct2.get("testVec2"));
   EXPECT_EQ(program.getUniform("testStruct2.testVec3"),testStruct2.get("testVec3"));
}

TEST(StructShaderTests, testStructBadAttrib)
{
   Program program("Test2");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/structFrag.fs"));
   EXPECT_EQ(0,program.create());

   GL_Structure testStruct;
   testStruct.addAttribute("testVec1");
   testStruct.addAttribute("testVec2");
   testStruct.addAttribute("testVec4");
   EXPECT_EQ(-1,program.addUniformStruct("test",testStruct));
   EXPECT_EQ(-1, testStruct.get("testVec1"));

}

TEST(StructShaderTests, testStructBadGet)
{
   Program program("Test2");
   EXPECT_EQ(0,program.addVertexShader("test/testAssets/basicVert.vs"));
   EXPECT_EQ(0,program.addFragmentShader("test/testAssets/structFrag.fs"));
   EXPECT_EQ(0,program.create());

   GL_Structure testStruct;
   testStruct.addAttribute("testVec1");
   testStruct.addAttribute("testVec2");
   testStruct.addAttribute("testVec3");
   EXPECT_EQ(0,program.addUniformStruct("test",testStruct));
   EXPECT_EQ(-1, testStruct.get("testVec4"));

}

TEST(StructShaderTests, testEmptyStruct)
{
   GL_Structure emptyStruct;
   EXPECT_EQ(-1,emptyStruct["attrb"]);
}

