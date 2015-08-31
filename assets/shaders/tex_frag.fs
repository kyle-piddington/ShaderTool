#version 330 core

in vec2 fragTexCoords;
in vec3 fragPos;
uniform sampler2D tex;
out vec4 color;

void main()
{
   color = texture(tex, vec2(fragTexCoords.x,-fragTexCoords.y));
}