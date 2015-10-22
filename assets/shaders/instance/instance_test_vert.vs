#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 offset;
out vec3 fragColor;

void main()
{
   vec2 pos = position * (gl_InstanceID / 100.0f);

   gl_Position = vec4(offset + pos, 0.0f, 1.0f);
   fragColor = color;
}