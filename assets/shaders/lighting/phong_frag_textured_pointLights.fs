#version 330 core

in vec3 fragPos;
in vec3 fragNor;
in vec2 fragTexCoords;

out vec4 color;
uniform mat4 V;


struct TexturedMaterial{
   sampler2D diffuse;
   sampler2D specular;
   sampler2D emission;
   float shininess;
};

uniform TexturedMaterial material;

struct PointLight{
   vec3 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   float constant;
   float linear;
   float quadratic;
};

#define NR_POINT_LIGHTS 8
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int numPointLights;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
   vec3 lightPosView = vec3(V * vec4(light.position,1.0));
   //Compute diffuse component
   vec3 lightDir = normalize(lightPosView-fragPos);
   float diff = max(dot(normal,lightDir),0.0f);

   vec3 reflectDir = reflect(-lightDir, normal);
   //Viewing is along the -Z axis
   float spec = pow(max(dot(reflectDir,viewDir),0.0),material.shininess);


   vec3 ambient  = light.ambient * vec3(texture(material.diffuse,fragTexCoords));
   vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse,fragTexCoords));
   vec3 specular = light.specular * spec * vec3(texture(material.specular,fragTexCoords));

   float dist    = length(lightPosView - fragPos);
   float attenuation = 1.0f / (light.constant + light.linear * dist +
             light.quadratic * (dist * dist));

   return (ambient + specular + diffuse ) * attenuation;
}


void main()
{
   //Move lightpos to view space

   vec3 norm = normalize(fragNor);
   vec3 result = vec3(0.0);

   //result += CalcDirLight(dirLight,norm,vec3(0,0,-1));
   vec3 viewDir = normalize(-fragPos);
   for(int i = 0; i < numPointLights; i++)
   {
      result += CalcPointLight(pointLights[i],norm,fragPos,viewDir);
   }
   vec3 emission = vec3(texture(material.emission,fragTexCoords));
   result += emission;
   if(numPointLights == 0)
   {
      result = texture(material.diffuse,fragTexCoords).xyz;
   }
   color = vec4(result,1.0) ;
}
