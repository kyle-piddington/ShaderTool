#version 330 core
in vec3 fragPos;
in vec3 fragNor;
in vec2 fragTexCoords;

out vec4 color;
#define MAX_DIFFUSE_TEXTURES 3
uniform sampler2D diffuseTextures[MAX_DIFFUSE_TEXTURES];
uniform int numDiffuseTextures;


#define MAX_SPECULAR_TEXTURES 2
uniform sampler2D specularTextures[MAX_SPECULAR_TEXTURES];
uniform int numSpecularTextures;

struct Material
{
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};
uniform Material material;

struct PointLight{
   vec3 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
  
   float constant;
   float linear;
   float quadratic;
};


#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform float shininess = 35;

uniform mat4 V;


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
   vec3 lightPosView = vec3(V * vec4(light.position,1.0));
   //Compute diffuse component
   vec3 lightDir = normalize(lightPosView-fragPos);
   float diff = max(dot(normal,lightDir),0.0f);

   vec3 reflectDir = normalize(lightDir + viewDir);
   //Viewing is along the -Z axis
   float spec = pow(max(dot(reflectDir,normal),0.0),shininess);


   vec3 ambient = vec3(0.0);
   vec3 diffuse = vec3(0.0);
   for(int diffTex = 0; diffTex < numDiffuseTextures; diffTex++)
   {
      ambient +=  max(vec3(0.0),light.ambient * vec3(texture(diffuseTextures[diffTex],fragTexCoords)));
      diffuse +=  max(vec3(0.0),light.diffuse * diff * vec3(texture(diffuseTextures[diffTex],fragTexCoords)));

   }
   ambient +=  max(vec3(0.0),light.ambient * material.ambient);
   diffuse +=  max(vec3(0.0),light.diffuse * diff * material.diffuse);

   vec3 specular = vec3(0.0);
   for(int specTex = 0; specTex < numSpecularTextures; specTex++)
   {
      specular += max(vec3(0.0),light.specular * spec * vec3(texture(specularTextures[specTex],fragTexCoords)));
   
   }
   specular += max(vec3(0.0),light.specular * spec * material.specular);
 
   float dist    = length(lightPosView - fragPos);
   float attenuation = 1.0f / (light.constant + light.linear * dist +
             light.quadratic * (dist * dist));

   return (ambient + specular + diffuse) * attenuation;
}


void main()
{
   vec3 result = vec3(0.0);
   vec3 norm = normalize(fragNor);
   vec3 viewDir = normalize(-fragPos);
   for(int i = 0; i < NR_POINT_LIGHTS; i++)
   {
      result += CalcPointLight(pointLights[i],norm,fragPos,viewDir);
   }
   color = vec4(result,1.0);
}
