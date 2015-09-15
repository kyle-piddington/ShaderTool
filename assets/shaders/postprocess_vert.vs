#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 vertTexCoords;

out vec2 fragTexCoords;

void main()
{
   gl_Position = vec4(position.x,position.z,0,1);
   fragTexCoords = vertTexCoords;
}