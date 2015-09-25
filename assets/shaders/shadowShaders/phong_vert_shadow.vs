#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;


//Out struct for light lookup
out VS_OUT {
   //Position in world space
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform mat3 NORM;
uniform mat4 lightSpaceMatrix;

void main()
{

   vs_out.FragPos = (V*M*vec4(position,1.0)).xyz;
   //Position the fragment in light space
   vs_out.FragPosLightSpace = lightSpaceMatrix * M * vec4(position,1.0);
   vs_out.Normal = NORM * normal;
   vs_out.TexCoords = texCoords;

   gl_Position = P*vec4(vs_out.FragPos,1.0);
  
}