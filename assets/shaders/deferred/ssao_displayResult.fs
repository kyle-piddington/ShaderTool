#version 330 core
in vec2 fragTexCoords;
out vec4 color;
uniform sampler2D aoTexture;
void main()
{
   color = vec4(texture(aoTexture,fragTexCoords).rrr,1.0);
}