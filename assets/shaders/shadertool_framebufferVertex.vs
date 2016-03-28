#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 vertTexCoords;

out vec3 fragPos;
out vec3 fragNor;
out vec2 fragTexCoords;


uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 N;

void main()
{
   vec4 fragPosition =   M * vec4(position,1.0);
   fragPos = fragPosition.xyz;
   gl_Position = P * V * fragPosition;
   fragNor = normalize(N * vec4(normal,0.0)).xyz;
   fragTexCoords = vertTexCoords;
}