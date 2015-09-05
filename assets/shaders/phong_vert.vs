#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat3 N;

out vec4 fragPosition;
out vec3 fragNor;


void main()
{
   gl_Position = P * V * M *  vec4(position, 1.0);
   fragPosition = (V * M * vec4(position, 1.0));
   fragNor = N * normal;
}