#version 330 core
struct testStruct
{
   vec3 testVec1;
   vec3 testVec2;
   vec3 testVec3;
};
uniform testStruct test;
uniform testStruct testStruct2;
out vec4 color;

void main()
{
    vec3 tmp = testStruct2.testVec1 + testStruct2.testVec2 + testStruct2.testVec3;
    color = vec4(tmp * (test.testVec1 + test.testVec2 + test.testVec3), 1.0f); // Set alle 4 vector values to 1.0f

}