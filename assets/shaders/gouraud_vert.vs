#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 M;
uniform mat4 N;
uniform mat4 V;
uniform mat4 P;


uniform float iGlobalTime;
out vec3 fragCol;

struct Material{
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

struct PointLight{
   vec3 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};



uniform Material material;
uniform PointLight light;


vec3 calcLighting(vec3 fragPos, vec3 fragNor)
{
   //Move lightpos to view space
   vec3 lightPosView = vec3(V * vec4(light.position,1.0));

   //Compute ambient component
   vec3 ambient = light.ambient * material.ambient;
   //Compute diffuse component
   vec3 nor=normalize(fragNor);
   vec3 lightDir = normalize(lightPosView-fragPos);
   float diff = max(dot(nor,lightDir),0.0f);
   vec3 diffuse = diff * light.diffuse * material.diffuse;

   vec3 reflectDir = reflect(-lightDir, nor);
   //Viewing is along the -Z axis
   vec3 viewDir = normalize(vec3(0,0,1) - fragPos);
   float spec = pow(max(dot(reflectDir,viewDir),0.0),material.shininess);
   vec3 specular = spec * material.specular * light.specular;

   vec3 result = (diffuse + ambient + specular );
   return result;

}

void main()
{

   gl_Position = P * V * M *  vec4(position, 1.0);
   vec3 fragPos = (V * M * vec4(position, 1.0)).xyz;
   vec3 fragNor = (N * vec4(normal,0.0)).xyz;
   fragCol = calcLighting(fragPos, fragNor);


}