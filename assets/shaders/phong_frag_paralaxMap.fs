
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
uniform sampler2D depthMap;
uniform PointLight pointLight;

uniform float iGlobalTime;
uniform vec2 iWindowResolution;


vec2 paralaxMapping(vec2 texCoords, vec3 viewDir)
{
   // number of depth layers
    const float minLayers = 10;
    const float maxLayers = 20;
    float height_scale = 0.2;

    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
  // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 p = viewDir.xy * height_scale; 
    vec2 deltaTexCoords = p / numLayers;

    vec2  currentTexCoords     = texCoords;
    float currentDepthMapValue = texture(depthMap, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
      currentTexCoords -= deltaTexCoords;
      // get depthmap value at current texture coordinates
      currentDepthMapValue = texture(depthMap, currentTexCoords ).r;  
      // get depth of next layer
      currentLayerDepth += layerDepth;
    }

    //Perform interpolation
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;
    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(depthMap, prevTexCoords).r - currentLayerDepth + layerDepth;

    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}

void main()
{

  vec3 viewDir = normalize(fs_in.tangentViewPos - fs_in.tangentFragPos);
  vec2 paralaxTexCoords = paralaxMapping(fs_in.fragTexCoords,viewDir);

  if(paralaxTexCoords.x > 1.0 || paralaxTexCoords.y > 1.0 || paralaxTexCoords.x < 0.0 || paralaxTexCoords.y < 0.0)
    discard;
 
  vec3 texColor = texture(material.diffuse,paralaxTexCoords).rgb;
  vec3 norm = 2*(texture(normalMap,paralaxTexCoords).xyz) - 1.0;
  
  //Ambient
  vec3 ambient = pointLight.ambient *  texColor;

  vec3 lightDir = normalize(fs_in.tangentLightPos - fs_in.tangentFragPos);
  float diff = max(dot(lightDir,norm),0.0);

  vec3 diffuse = pointLight.diffuse * diff * texColor;



  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
  vec3 specular = pointLight.specular * spec * texture(material.specular,paralaxTexCoords).r;

  vec3 result = ambient + diffuse + specular;

  color = vec4(result,1.0);
}
