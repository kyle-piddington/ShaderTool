#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 offset;
out vec3 fragColor;

uniform float time;
void main()
{
   vec2 pos = position * ( (0.5 * sin(time + gl_InstanceID * 6.28 / 100.0)) + 0.75);

   gl_Position = vec4(offset + pos, 0.0f, 1.0f);
   fragColor = color;
}