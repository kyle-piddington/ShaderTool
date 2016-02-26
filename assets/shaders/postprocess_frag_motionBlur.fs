/**
 * Screen space motion blur
 * Code/Ideas from
 * https://developer.nvidia.com/gpugems/GPUGems3/gpugems3_ch27.html
 * 
 */
#version 330 core
in vec2 fragTexCoords;
out vec4 color;
uniform sampler2D depth;
uniform sampler2D screenTexture;
uniform mat4 g_ViewProjectionInverseMatrix;
uniform mat4 g_PreviousViewProjectionMatrix;
uniform int g_numSamples = 4;

void main()
{
   //Get the current depth value
   float zOverW = texture(depth,fragTexCoords).r;
   vec4 H = vec4(fragTexCoords.x * 2 - 1, (1 - fragTexCoords.y) * 2 - 1, zOverW, 1);
   //Calculate the Depth-skewed world coordinates
   vec4 D = g_ViewProjectionInverseMatrix * H;
   vec4 worldPos = D / D.w; //Divide by the W component to return to World Coordinates
   
   //Get the previous viewspace position
   vec4 prevPos = g_PreviousViewProjectionMatrix * worldPos;
   prevPos /= prevPos.w;
   vec2 velocity = (H.xy - prevPos.xy)/(g_numSamples*3.f);
   
   vec4 fColor = texture(screenTexture,fragTexCoords);
   vec2 sampleCoords = fragTexCoords + velocity;
   for(int i = 1; i < g_numSamples; i++)
   {
      fColor += texture(screenTexture,sampleCoords);
      sampleCoords += velocity;
   }
   fColor /= g_numSamples;
   color = fColor;
}