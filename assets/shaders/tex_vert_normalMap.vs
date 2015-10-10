#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 vertTexCoords;
layout (location = 3) in vec3 tangent;


uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out VS_OUT {
    vec3 fragPos;
    vec2 fragTexCoords;
    vec3 tangentLightPos;
    vec3 tangentViewPos;
    vec3 tangentFragPos;
} vs_out;

struct PointLight{
   vec3 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
  
   float constant;
   float linear;
   float quadratic;
};
uniform PointLight pointLight;

uniform vec3 viewPos;


void main()
{
   gl_Position = P * V * M *  vec4(position, 1.0);
   //Calculate TBN matrix
   vec3 T = normalize(vec3(M * vec4(tangent, 0.0)));
   vec3 N = normalize(vec3(M * vec4(normal, 0.0)));
   // re-orthogonalize T with respect to N
   T = normalize(T - dot(T, N) * N);
   vec3 B = cross(T,N);

   vs_out.fragPos = vec3(M*vec4(position,1.0));
   vs_out.fragTexCoords = vertTexCoords;
   mat3 TBN = mat3(T, B, N);
   vs_out.tangentLightPos = TBN * pointLight.position;
   vs_out.tangentViewPos = TBN * viewPos;
   vs_out.tangentFragPos = TBN * vs_out.fragPos;
   
}