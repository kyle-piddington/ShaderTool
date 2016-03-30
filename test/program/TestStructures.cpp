#include <catch/catch.hpp>
#include "Program.h"
TEST_CASE("Basic Program Querying" , "[Introspection]")
{
   Program program("test");
   program.addVertexShader("assets/test/shaders/test_shaderBasic.vs");
   program.addFragmentShader("assets/test/shaders/test_shaderBasic.fs");
   program.create();

   //Query and bind basic attributes
   REQUIRE_NOTHROW(program.getUniform("aInt").bind(-1));
   REQUIRE_NOTHROW(program.getUniform("aVec2").bind(glm::vec2(0,0)));
   REQUIRE_NOTHROW(program.getUniform("aMat3").bind(glm::mat3(1.0)));

   //Test to make sure assertions work
   REQUIRE_THROWS(program.getUniform("notExist").bind(10));
   REQUIRE_THROWS(program.getUniform("aVec2").bind(10));

}

TEST_CASE("Array Program Querying", "[Introspection]")
{
   Program program("test");
   program.addVertexShader("assets/test/shaders/test_shaderArray.vs");
   program.addFragmentShader("assets/test/shaders/test_shaderBasic.fs");

   //Check to see if you can query an array.
   REQUIRE_NOTHROW(program.getUniform("array1")[0].bind(5));
   REQUIRE_NOTHROW(program.getUniform("array1")[9] . bind(10));

   //Size limits
   REQUIRE_THROWS(program.getUniform("array1")[-1].bind(0));
   REQUIRE_THROWS(program.getUniform("array1")[10].bind(0));

   //Bind types
   REQUIRE_THROWS(program.getUniform("array1")[10].bind(glm::vec3(1.0)));

}


TEST_CASE("Struct Program Querying", "[Introspection]")
{
   Program program("test");
   program.addVertexShader("assets/test/shaders/test_shaderStruct.vs");
   program.addFragmentShader("assets/test/shaders/test_shaderBasic.fs");

   REQUIRE_NOTHROW(program.getUniform("tStruct")["field1"].bind(4));
   REQUIRE_NOTHROW(program.getUniform("tStruct2")["field2"].bind(glm::vec3(1.0)));
   REQUIRE_NOTHROW(program.getUniform("tStruct2")["field3"].bind(glm::mat3(1.0)));

}

TEST_CASE("Struct In Array Querying", "[Introspection]")
{
   Program program("test");
   program.addVertexShader("assets/test/shaders/test_arrStruct.vs");
   program.addFragmentShader("assets/test/shaders/test_arrBasic.fs");
   program.create();
   /**
    * Bind to this kind of structure:
    * struct a_struct
    * {
    *    int field1;
    *    vec2 field2;
    *    mat3 field3;
    * }
    * uniform a_struct arr[3];
    */
   REQUIRE_NOTHROW(program.getUniform("arr")[0]["field1"].bind(4));
   REQUIRE_NOTHROW(program.getUniform("arr")[1]["field2"].bind(glm::vec3(1.0)));
   REQUIRE_NOTHROW(program.getUniform("arr")[2]["field3"].bind(glm::mat3(1.0)));
}
TEST_CASE("Array in Struct Querying", "[Introspection]")
{
   Program program("test");
   program.addVertexShader("assets/test/shaders/test_structArr.vs");
   program.addFragmentShader("assets/test/shaders/test_shaderBasic.fs");
   program.create();
   /**
    * Bind to this kind of structure:
    * struct a_struct
    * {
    *    int arr[3];
    * }
    * uniform a_struct struct
    */
   REQUIRE_NOTHROW(program.getUniform("struct")["arr"][0].bind(3.0));
}
