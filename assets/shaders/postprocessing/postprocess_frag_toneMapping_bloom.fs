#version 330 core
in vec2 fragTexCoords;
out vec4 color;

uniform sampler2D screenTexture;
uniform sampler2D bloomTexture;
void main()
{

      const float exposure = 1.1;
      const float gamma = 2.2;
      vec3 hdrColor = texture(screenTexture, fragTexCoords).rgb; 
      if(gl_FragCoord.x < 800)
         hdrColor += texture(bloomTexture, fragTexCoords).rgb;
     
       // Reinhard tone mapping
      vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
         // Gamma correction 
      mapped = pow(mapped, vec3(1.0 / gamma));
     
      color = vec4(mapped, 1.0);
   
  

}