#version 330 core
layout (location = 0) in vec3 position;

out vec3 fragTexCoords;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

void main()
{
   gl_Position = P * V * M * vec4(position,1.0);
   fragTexCoords = position;
}