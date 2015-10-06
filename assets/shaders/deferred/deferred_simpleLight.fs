#version 330 core
out vec4 color;
in vec2 fragTexCoords;

uniform sampler2D posTexture;
uniform sampler2D norTexture;
uniform sampler2D albedo_specTexture;

struct Light{
   vec3 pos;
   vec3 color;

   float Linear;
   float Quadratic;

};

const int NR_LIGHTS = 32;
uniform Light lights[NR_LIGHTS];
uniform vec3 viewPos;

void main()
{
   vec3 fragPos = texture(posTexture,fragTexCoords).rgb;
   vec3 fragNor = texture(norTexture, fragTexCoords).rgb;
   vec3 albedo = texture(albedo_specTexture,fragTexCoords).rgb;
   float specularIntensity = texture(albedo_specTexture,fragTexCoords).a;

   vec3 lighting = albedo * 0.1; //Ambient
   vec3 viewDir = normalize(viewPos-fragPos);

   for(int i = 0; i < NR_LIGHTS; i++)
   {
      vec3 lightDir = normalize(lights[i].pos - fragPos);
      vec3 diffuse = max(dot(fragNor,lightDir),0.0) * albedo * lights[i].color;
      
      vec3 halfwayDir = normalize(lightDir + viewDir);
      float spec = pow(max(dot(fragNor, halfwayDir), 0.0), 16.0);
      vec3 specular = lights[i].color * spec * specularIntensity;

      float dist = length(lights[i].pos - fragPos);
      float attenuation = 1.0 / (1.0 + lights[i].Linear * dist + lights[i].Quadratic * dist * dist);
      diffuse *= attenuation;
      specular *= attenuation;
      lighting += diffuse + specular;

   }
   //lighting = fragPos;
   color = vec4(lighting,1.0);

}