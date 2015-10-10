
#version 330 core

out vec4 color;

in VS_OUT {
    vec3 fragPos;
    vec2 fragTexCoords;
    vec3 tangentLightPos;
    vec3 tangentViewPos;
    vec3 tangentFragPos;
} fs_in;

struct PointLight{
   vec3 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;

   float constant;
   float linear;
   float quadratic;
};

struct TexturedMaterial{
   sampler2D diffuse;
   sampler2D specular;
   sampler2D emission;
   float shininess;
};
uniform TexturedMaterial material;
uniform sampler2D normalMap;
uniform PointLight pointLight;


void main()
{
  vec3 texColor = texture(material.diffuse,fs_in.fragTexCoords).rgb;
  vec3 norm = 2*(texture(normalMap,fs_in.fragTexCoords).xyz) - 1.0;

  //Ambient
  vec3 ambient = pointLight.ambient *  texColor;

  vec3 lightDir = normalize(fs_in.tangentLightPos - fs_in.tangentFragPos);
  float diff = max(dot(lightDir,norm),0.0);

  vec3 diffuse = pointLight.diffuse * diff * texColor;

  vec3 viewDir = normalize(fs_in.tangentViewPos - fs_in.tangentFragPos);


  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
  vec3 specular = pointLight.specular * spec * texture(material.specular,fs_in.fragTexCoords).r;

  vec3 result = ambient + diffuse + specular;

  color = vec4(result,1.0);
}
