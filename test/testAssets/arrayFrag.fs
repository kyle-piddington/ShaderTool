#version 330 core
struct testStruct
{
   vec3 testVec1;
   vec3 testVec2;
   vec3 testVec3;
};
uniform int intArr[10];
uniform testStruct structArr[10];
out vec4 color;

void main()
{
   vec3 tmp;
   for(int i = 0; i < 10; i++)
   {
      tmp = (structArr[i].testVec1 + structArr[i].testVec2 + structArr[i].testVec3)*intArr[i];
   }
   color = vec4(tmp , 1.0f); // Set alle 4 vector values to 1.0f

}