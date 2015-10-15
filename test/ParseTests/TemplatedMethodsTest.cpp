#include <gtest/gtest.h>
#include <GLFW/glfw3.h>
#include <GLSLParser.h>
#include <glm/glm.hpp>
TEST(TemplateMethodTest,TestBindIntSuccess)
{
   GLSLParser::UniformObject uo("iTest",GLSLParser::GLSLinteger);
   ASSERT_NO_THROW(uo.bind(5));
}

TEST(TemplateMethodTest, TestBindIntFail)
{
   GLSLParser::UniformObject uo("fTest",GLSLParser::GLSLinteger);
   ASSERT_THROW(uo.bind(0.5f),GLSLParser::GLSLTypeException);
}

TEST(TemplateMethodTest, testBindFloatSuccess)
{
   GLSLParser::UniformObject uo("fTest",GLSLParser::GLSLfloatingPt);
   ASSERT_NO_THROW(uo.bind(0.5f));
}

TEST(TemplateMethodTest, testBindFloatFailure)
{
   GLSLParser::UniformObject uo("iTest",GLSLParser::GLSLfloatingPt);
   ASSERT_THROW(uo.bind(5),GLSLParser::GLSLTypeException);
}

TEST(TemplateMethodTest, testBindBoolSuccess)
{
   GLSLParser::UniformObject uo("bTest",GLSLParser::GLSLboolean);
   ASSERT_NO_THROW(uo.bind(true));
}

TEST(TemplateMethodTest, testBindBoolFailure)
{
   GLSLParser::UniformObject uo("bTest",GLSLParser::GLSLboolean);
   ASSERT_THROW(uo.bind(5),GLSLParser::GLSLTypeException);
}

TEST(TemplateMethodTest, testGlmVec2Success)
{
   GLSLParser::UniformObject uo("v2Test",GLSLParser::GLSLvector2);
   ASSERT_NO_THROW(uo.bind(glm::vec2(1.0,2.0)));
}

TEST(TemplateMethodTest, testGlmVec2Failure)
{
   GLSLParser::UniformObject uo("v2Test",GLSLParser::GLSLvector2);
   ASSERT_THROW(uo.bind(1),GLSLParser::GLSLTypeException);
}