#version 330 core

in vec2 fragTexCoords;

#define MAX_DIFFUSE_TEXTURES 3
uniform sampler2D diffuseTextures[MAX_DIFFUSE_TEXTURES];
uniform int numDiffuseTextures;

out vec4 color;

void main()
{
   color = vec4(0.0,0.0,0.0,1.0);
   for(int i = 0; i < numDiffuseTextures; i++)
   {
      color += texture(diffuseTextures[i], vec2(fragTexCoords.x,fragTexCoords.y));
   }

}