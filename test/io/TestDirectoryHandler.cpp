#include <catch/catch.hpp>
#include "DirectoryHandler.h"
TEST_CASE("Directory Listing" , "[IO]")
{
   std::vector<std::string> paths = DirectoryHandler::listDirectory("assets/test");
   REQUIRE(paths.size() == 1);
   REQUIRE(paths[0] == "shaders");

   paths = DirectoryHandler::listDirectory("assets/test/shaders");
   REQUIRE(paths.size() == 2);
   REQUIRE(paths[0] == "test_shaderBasic.fs");
   REQUIRE(paths[1] == "test_shaderBasic.vs");
   
}

TEST_CASE("Directory Listing Extensions" , "[IO]")
{
   std::vector<std::string> paths;
   paths = DirectoryHandler::listDirectory("assets/test/shaders","fs");
   REQUIRE(paths.size() == 1);
   REQUIRE(paths[0] == "test_shaderBasic.fs");
}
