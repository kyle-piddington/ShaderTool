#version 330 core

in vec2 fragTexCoords;

uniform sampler2D tex;
out vec4 color;

void main()
{
   vec4 texColor = texture(tex, vec2(fragTexCoords.x,fragTexCoords.y));
   color = texColor;
}