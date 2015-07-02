#version 330 core

in vec4 vertexColor;
in vec2 fragTexCoords;
out vec4 color;

uniform sampler2D tex0;
uniform sampler2D tex1;
void main()
{
   vec2 texCoords = vec2(fragTexCoords.x, -fragTexCoords.y);
   color =  mix(texture(tex1,texCoords) ,texture(tex0, texCoords), 0.5)
             * vec4(vertexColor.xyz, 1.0f);  
}