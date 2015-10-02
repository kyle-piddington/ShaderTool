#version 330 core
in vec2 fragTexCoords;
out vec4 color;

uniform sampler2D screenTexture;
void main()
{
   const float exposure = 1.2;
   const float gamma = 1.4;
   vec3 hdrColor = texture(screenTexture, fragTexCoords).rgb;
  
    // Reinhard tone mapping
   vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
      // Gamma correction 
   mapped = pow(mapped, vec3(1.0 / gamma));
  
   color = vec4(mapped, 1.0);
}