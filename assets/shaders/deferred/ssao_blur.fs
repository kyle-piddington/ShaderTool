#version 330 core
in vec2 fragTexCoords;
layout (location = 0) out float ssaoOutput;
uniform sampler2D ssaoInput;

void main()
{
   vec2 texelSize = 1.0/vec2(textureSize(ssaoInput,0));
   float result = 0.0;
   //Sample 16 texels surrounding the pixel and avg
   for(int x = -2; x < 2; x++)
   {
      for(int y = -2; y < 2; y++)
      {
         vec2 offset = vec2(float(x),float(y)) * texelSize;
         result += texture(ssaoInput,fragTexCoords + offset).r;
      }
   }
   ssaoOutput = result/16;

}