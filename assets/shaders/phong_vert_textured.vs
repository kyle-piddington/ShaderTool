#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 vertTexCoords;


uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat3 N;

out vec3 fragPos;
out vec3 fragNor;
out vec2 fragTexCoords;
void main()
{
   gl_Position = P * V * M *  vec4(position, 1.0);
   fragPos = (V * M * vec4(position, 1.0)).xyz;
   fragNor = N * normal;
   fragTexCoords = vertTexCoords;
}