#version 330 core
out vec4 color;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

struct PointLight{
   vec3 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   float constant;
   float linear;
   float quadratic;
};

uniform PointLight pLight;

uniform mat4 V;

float calcShadow(vec4 fragPosLightSpace)
{
   vec3 lightPosView = vec3(V * vec4(pLight.position,1.0f));
   //Compute diffuse component
   vec3 lightDir = normalize(lightPosView-fs_in.FragPos);
  
   //Scale to NDC
   vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
   //Convert to txcoords
   projCoords = projCoords * 0.5 + 0.5;

   float bias = max(0.05 * (1.0 - dot(normalize(fs_in.Normal), lightDir)), 0.005);  

   float closestDepth = texture(shadowMap, projCoords.xy).r; 
   
   float currentDepth = projCoords.z;
    // Check whether current frag pos is in shadow
   float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

   if(projCoords.z > 1.0)
        shadow = 0.0;

   return shadow;
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
   vec3 lightPosView = vec3(V * vec4(light.position,1.0f));
   //Compute diffuse component
   vec3 lightDir = normalize(lightPosView-fragPos);
   
   vec3 halfwayDir = normalize(lightDir + viewDir);
   //Viewing is along the -Z axis
   float diff = max(dot(normal,lightDir),0.0f);
   float spec = pow(max(dot(normal,halfwayDir),0.0f),64.0f);


   vec3 ambient  = light.ambient * vec3(texture(diffuseTexture,fs_in.TexCoords));
   vec3 diffuse  =  light.diffuse * diff * vec3(texture(diffuseTexture,fs_in.TexCoords));
   vec3 specular = light.specular * spec;
   
   float dist    = length(lightPosView - fragPos);
   float attenuation = 1.0f / (light.constant + light.linear * dist +
             light.quadratic * (dist * dist));

   return (ambient  + specular + diffuse) * attenuation;
}

void main()
{
   vec3 viewDir = normalize(-fs_in.FragPos);
   vec3 result = CalcPointLight(pLight,normalize(fs_in.Normal),fs_in.FragPos,viewDir);
   float shadow = calcShadow(fs_in.FragPosLightSpace);
   vec3 shadowReduction  = shadow * (pLight.ambient * vec3(texture(diffuseTexture,fs_in.TexCoords)));
  
   color = vec4(result - shadowReduction , 1.0);
}