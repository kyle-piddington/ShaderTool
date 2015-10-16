#include <gtest/gtest.h>
#include <GLFW/glfw3.h>
#include <GLSLParser.h>
#include <glm/glm.hpp>

TEST(overloadedMethodsTest,TestBindIntSuccess)
{
   GLSLParser::UniformObject uo("iTest",GLSLParser::GLSLinteger);
   ASSERT_NO_THROW(uo.bind(5));
}

TEST(overloadedMethodsTest, TestBindIntFail)
{
   GLSLParser::UniformObject uo("fTest",GLSLParser::GLSLinteger);
   ASSERT_THROW(uo.bind(0.5f),GLSLParser::GLSLTypeException);
}

TEST(overloadedMethodsTest, testBindFloatSuccess)
{
   GLSLParser::UniformObject uo("fTest",GLSLParser::GLSLfloatingPt);
   ASSERT_NO_THROW(uo.bind(0.5f));
}

TEST(overloadedMethodsTest, testBindFloatFailure)
{
   GLSLParser::UniformObject uo("iTest",GLSLParser::GLSLfloatingPt);
   ASSERT_THROW(uo.bind(5),GLSLParser::GLSLTypeException);
}

TEST(overloadedMethodsTest, testBindBoolSuccess)
{
   GLSLParser::UniformObject uo("bTest",GLSLParser::GLSLboolean);
   ASSERT_NO_THROW(uo.bind(true));
}

TEST(overloadedMethodsTest, testBindBoolFailure)
{
   GLSLParser::UniformObject uo("bTest",GLSLParser::GLSLboolean);
   ASSERT_THROW(uo.bind(5),GLSLParser::GLSLTypeException);
}

TEST(overloadedMethodsTest, testGlmVec2Success)
{
   GLSLParser::UniformObject uo("v2Test",GLSLParser::GLSLvector2);
   ASSERT_NO_THROW(uo.bind(glm::vec2(1.0,2.0)));
}

TEST(overloadedMethodsTest, testGlmVec2Failure)
{
   GLSLParser::UniformObject uo("v2Test",GLSLParser::GLSLvector2);
   ASSERT_THROW(uo.bind(1),GLSLParser::GLSLTypeException);
}