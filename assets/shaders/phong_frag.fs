#version 330 core

in vec3 fragPos;
in vec3 fragNor;

out vec4 color;
uniform mat4 V;

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

   float constant;
   float linear;
   float quadratic;
};

struct DirectionalLight{
   vec3 direction;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular
};

uniform Material material;
uniform Light light;




void main()
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
   float spec = pow(max(dot(reflectDir,viewDir),0.0),32);
   vec3 specular = spec * material.specular * light.specular;
   //Compute final result
   //

   float dist    = length(light.position - FragPos);
   float attenuation = 1.0f / (light.constant + light.linear * dist +
             light.quadratic * (dist * dist));

   vec3 result = (diffuse + ambient + specular) * attenuation;

   color = vec4(result,1.0);
}