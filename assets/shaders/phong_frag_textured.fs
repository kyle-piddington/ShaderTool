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


//#define NR_POINT_LIGHTS 5
//uniform PointLight pointLights[NR_POINT_LIGHTS];
//uniform int numPointLights;
uniform PointLight pointLight;

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
   
   float dist    = length(light.position - fragPos);
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
#define NR_DIR_LIGHTS 5
uniform DirectionalLight directionalLights[NR_DIR_LIGHTS];
uniform int numDirectionalLights;


vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{

   vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
   float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine results
   vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, fragTexCoords));
   vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, fragTexCoords));
   vec3 specular = light.specular * spec * vec3(texture(material.specular, fragTexCoords));
   return (ambient + diffuse + specular);
}


void main()
{
   //Move lightpos to view space

   vec3 norm = normalize(fragNor);
   vec3 result = vec3(0.0);

   //result += CalcDirLight(dirLight,norm,vec3(0,0,-1));
   result += CalcPointLight(pointLight,norm,fragPos,normalize(-fragPos));
   vec3 emission = vec3(texture(material.emission,fragTexCoords));
   result += emission;

   color = vec4(result,1.0);
}