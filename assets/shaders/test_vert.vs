#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform vec3 offset;
out vec4 vertexColor;
void main()
{
   gl_Position = vec4(position.x + offset.x, position.y + offset.y, position.z + offset.z, 1.0);
   vertexColor = vec4(color,1.0);

}