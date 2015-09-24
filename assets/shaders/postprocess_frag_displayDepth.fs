#version 330 core
in vec2 fragTexCoords;
out vec4 color;

uniform sampler2D screenTexture;
void main()
{
   color = vec4(texture(screenTexture, fragTexCoords).rrr,1.0);
}