#version 330 core

in vec3 fragPos;
in vec3 fragNor;

out vec4 color;
uniform mat4 V;


uniform vec3 objColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float specularStrength;

void main()
{
   //Move lightpos to view space
   vec3 lightPosView = vec3(V * vec4(lightPos,1.0));

   //Compute ambient component
   float ambientStrength = 0.1f;
   vec3 ambient = ambientStrength * lightColor;
   //Compute diffuse component
   vec3 nor=normalize(fragNor);
   vec3 lightDir = normalize(lightPosView-fragPos);
   float diff = max(dot(nor,lightDir),0.0f);
   vec3 diffuse = diff * lightColor;

   vec3 reflectDir = reflect(-lightDir, nor);
   //Viewing is along the -Z axis
   vec3 viewDir = normalize(vec3(0,0,1) - fragPos);
   float spec = pow(max(dot(reflectDir,viewDir),0.0),32);
   vec3 specular = spec * specularStrength * lightColor;
   //Compute final result
   vec3 result = (diffuse + ambient + specular) * objColor;

   color = vec4(result,1.0);
}