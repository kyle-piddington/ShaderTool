#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 vertTexCoords;

out vec2 fragTexCoords;

void main()
{
   gl_Position = vec4(position, 1.0);
   fragTexCoords = vertTexCoords;
}