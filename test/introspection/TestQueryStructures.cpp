#include <catch/catch.hpp>
#include "StructUniformObject.h"
#include "ArrayUniformObject.h"
void extract(std::shared_ptr<UniformObject> structObj, std::string name, bool result = true)
{
   if(result)

   {
      const UniformObject & obj = (*structObj)[name];
      REQUIRE(obj.isValid());
   }    

   else
   {
     REQUIRE_THROWS((*structObj)[name]);
   } 
}

void extract(std::shared_ptr<UniformObject> arrayObj, int idx, bool result = true)
{
   if(result)
   {
      const UniformObject & obj = (*arrayObj)[idx];
      REQUIRE(obj.isValid());
   }    
   else
   {
     REQUIRE_THROWS((*arrayObj)[idx]);
   } 
}

TEST_CASE("Struct Querying" , "[Introspection]")
{
   std::shared_ptr<UniformObject> subObj = std::make_shared<UniformObject>("subObj",GLSLType::GLSLfloatingPt, 1);
   std::shared_ptr<StructUniformObject> structObj = std::make_shared<StructUniformObject>("structObj");
   structObj->addUniformObject(subObj);
   extract(structObj,"subObj");
}

TEST_CASE("Struct Querying Bad" , "[Introspection]")
{
   std::shared_ptr<UniformObject> subObj = std::make_shared<UniformObject>("subObj",GLSLType::GLSLfloatingPt, 1);
   std::shared_ptr<StructUniformObject> structObj = std::make_shared<StructUniformObject>("structObj");
   structObj->addUniformObject(subObj);
   extract(structObj,"notFound",false);
}

TEST_CASE("Array Querying", "[Introspection]")
{
   std::vector<std::shared_ptr<UniformObject>> elements;
   std::shared_ptr<ArrayUniformObject> arrayObj;
   for(int i = 0; i < 10; i++)
   {
      elements.push_back(std::make_shared<UniformObject>("array["+std::to_string(i)+"]",GLSLType::GLSLinteger,i));
   }
   arrayObj = std::make_shared<ArrayUniformObject>("array",elements);
   for(int i = 0; i < 10; i++)
   {
      extract(arrayObj,i);

   }
   extract(arrayObj,-1,false);
   extract(arrayObj,11,false);
}



