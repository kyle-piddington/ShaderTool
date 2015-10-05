#version 330 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedoSpec;

in vec3 fragPos;
in vec3 fragNor;
in vec2 fragTexCoords;

#define MAX_DIFFUSE_TEXTURES 3
uniform sampler2D diffuseTextures[MAX_DIFFUSE_TEXTURES];
uniform int numDiffuseTextures;


#define MAX_SPECULAR_TEXTURES 2
uniform sampler2D specularTextures[MAX_SPECULAR_TEXTURES];
uniform int numSpecularTextures;

void main()
{    
    // Store the fragment position vector in the first gbuffer texture
    gPosition = fragPos;
    // Also store the per-fragment normals into the gbuffer
    gNormal = normalize(fragNor);
    // And the diffuse per-fragment color
   gAlbedoSpec = vec4(0.0);
   for(int i = 0; i < numDiffuseTextures; i++)
   {
      gAlbedoSpec.rgb += texture(diffuseTextures[i], fragTexCoords).rgb;
   }
   for(int i = 0; i < numSpecularTextures; i++)
   {
      gAlbedoSpec.a += texture(specularTextures[i], fragTexCoords).r;
   }
 
}  