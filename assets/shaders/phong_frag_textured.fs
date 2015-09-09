#version 330 core

/**
 * Basic Phong lighting shader, can take varying amounts of point lights and directional lights. Also
 * includes support for emmision maps.
 */
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


#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

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
   vec3 diffuse  =  light.diffuse * diff * vec3(texture(material.diffuse,fragTexCoords));
   vec3 specular = light.specular * spec * vec3(texture(material.specular,fragTexCoords));
   
   float dist    = length(lightPosView - fragPos);
   float attenuation = 1.0f / (light.constant + light.linear * dist +
             light.quadratic * (dist * dist));

   return (ambient + specular + diffuse) * attenuation;
}


//Directional lighting
struct DirectionalLight
{
   vec3 direction;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};
//#define NR_DIR_LIGHTS 5
//uniform DirectionalLight directionalLights[NR_DIR_LIGHTS];
//uniform int numDirectionalLights;
uniform DirectionalLight dirLight;

vec3 CalcDirLight(DirectionalLight dLight, vec3 normal, vec3 viewDir)
{

   vec3 lightDir = normalize(-dLight.direction);
    // Diffuse shading
   float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine results
   vec3 ambient  = dLight.ambient  * vec3(texture(material.diffuse, fragTexCoords));
   vec3 diffuse  = dLight.diffuse  * diff * vec3(texture(material.diffuse, fragTexCoords));
   vec3 specular = dLight.specular * spec * vec3(texture(material.specular, fragTexCoords));
   return (ambient + diffuse + specular);
}

struct FlashLight{
   vec3  position;
   vec3  direction;
   float cutOff;
   float outerCutOff;
   

   float constant;
   float linear;
   float quadratic;
  
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

};
uniform FlashLight flashLight;

vec3 CalcSpotLight(FlashLight light,  vec3 normal, vec3 position, vec3 viewDir)
{
   vec3 lightPosView = vec3(V * vec4(light.position,1.0));
   vec3 lightDirView = normalize(vec3(V * normalize(vec4(light.direction,0.0))));
   vec3 lightDir = normalize(lightPosView - position);
   //Point light calculation
   float diff = max(dot(normal,lightDir),0.0f);
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(reflectDir,viewDir),0.0),material.shininess);

   vec3 ambient  = light.ambient * vec3(texture(material.diffuse,fragTexCoords));
   vec3 diffuse  =  light.diffuse * diff * vec3(texture(material.diffuse,fragTexCoords));
   vec3 specular = light.specular * spec * vec3(texture(material.specular,fragTexCoords));
   //Light intensity for radius, interpolation between the two
   
   //This is actually cos(theta)
   float theta = dot(lightDir, -lightDirView);
   
   float epsilon = (cos(light.cutOff) - cos(light.outerCutOff));
   float intensity = clamp((theta - cos(light.outerCutOff)) / epsilon, 0.0, 1.0);
   
   diffuse *= intensity;
   specular *= intensity;

   vec3 circleCenter = lightPosView + lightDirView * length(lightPosView - position)*theta;
   /*
   float maskCosTheta = ((circleCenter.x - position.x)/length(circleCenter - position));
   float maskSinTheta = ((circleCenter.y - position.y)/length(circleCenter - position));
   float maskR = length(circleCenter - position);
   maskR /= tan(light.outerCutOff)*length(lightPosView - circleCenter);
   vec3 lightMask = texture(light.mask,vec2(maskR * maskCosTheta, maskR * maskSinTheta)*0.5 + vec2(0.5)).xyz;
   diffuse *= lightMask;
   specular *= lightMask;
   */
   float dist    = length(lightPosView - fragPos);
   float attenuation = 1.0f / (light.constant + light.linear * dist +
             light.quadratic * (dist * dist));

   return vec3(ambient + diffuse + specular) * attenuation;

}

void main()
{
   //Move lightpos to view space

   vec3 norm = normalize(fragNor);
   vec3 result = vec3(0.0);

   //result += CalcDirLight(dirLight,norm,vec3(0,0,-1));
   vec3 viewDir = normalize(-fragPos);
   
   result += CalcDirLight(dirLight, norm, viewDir);
   result += CalcSpotLight(flashLight,norm,fragPos,viewDir);
   for(int i = 0; i < NR_POINT_LIGHTS; i++)
   {
      result += CalcPointLight(pointLights[i],norm,fragPos,viewDir);
   }
   vec3 emission = vec3(texture(material.emission,fragTexCoords));
   result += emission;
   //result += vec(0.5);
   color = vec4(result,1.0) ;
}