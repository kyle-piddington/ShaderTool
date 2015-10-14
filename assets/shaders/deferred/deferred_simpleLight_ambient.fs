#version 330 core
out vec4 color;
in vec2 fragTexCoords;

uniform sampler2D ambient;
uniform sampler2D posTexture;
uniform sampler2D norTexture;
uniform sampler2D albedo_specTexture;

struct Light{
   vec3 pos;
   vec3 color;

   float Linear;
   float Quadratic;


};

uniform Light light;
uniform vec3 viewPos;
uniform float time;

void main()
{
   vec3 fragPos = texture(posTexture,fragTexCoords).rgb;
   vec3 fragNor = texture(norTexture, fragTexCoords).rgb;
   vec3 albedo = texture(albedo_specTexture,fragTexCoords).rgb;
   float specularIntensity = texture(albedo_specTexture,fragTexCoords).a;

   vec3 lighting = vec3(0.25) * albedo;

   if(gl_FragCoord.x < (sin(time)*0.5 + 0.5) * 800)
   {
      lighting =  albedo*0.3*texture(ambient,fragTexCoords).rrr; //Ambient
   }
   vec3 viewDir = normalize(viewPos-fragPos);


   vec3 lightDir = normalize(light.pos - fragPos);
   vec3 diffuse = max(dot(fragNor,lightDir),0.0) * albedo * light.color;

   vec3 halfwayDir = normalize(lightDir + viewDir);
   float spec = pow(max(dot(fragNor, halfwayDir), 0.0), 16.0);
   vec3 specular = light.color * spec * specularIntensity;

   float dist = length(light.pos - fragPos);
   float attenuation = 1.0 / (1.0 + light.Linear * dist + light.Quadratic * dist * dist);
   diffuse *= attenuation;
   specular *= attenuation;

   lighting += diffuse + specular;

   
   //lighting = fragPos;
   color = vec4(lighting,1.0);


}