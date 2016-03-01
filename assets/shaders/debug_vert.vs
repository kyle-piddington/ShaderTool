#version 330 core

layout (location = 0) in vec3 position;


uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform vec3 arr[10];

struct blarp
{
   float ex;
   float ey;
   float ez;
};
uniform blarp vicVectr;

void main()
{
   vec3 sum;
   sum+= arr[0] + arr[4] + arr[9];
   gl_Position = P * V * M *  vec4(position + sum + vicVectr.ex + vicVectr.ey + vicVectr.ez, 1.0);
}