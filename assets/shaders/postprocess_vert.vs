#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 vertTexCoords;

out vec2 fragTexCoords;

uniform mat4 M;
void main()
{
   gl_Position = M * vec4(position.x,position.z,0,1);
   fragTexCoords = vertTexCoords;
}