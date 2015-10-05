#version 330 core
in vec2 fragTexCoords;
out vec4 color;

uniform sampler2D posTexture;
uniform sampler2D norTexture;
uniform sampler2D albedo_specTexture;
uniform int renderType;
void main()
{
   if(renderType == 0)
   {

      color = texture(posTexture, fragTexCoords);
   }
   else if(renderType == 1)
   {

      color = texture(norTexture,fragTexCoords);
   }
   else if(renderType == 2)
   {
      color = vec4(texture(albedo_specTexture,fragTexCoords).rgb,1.0);
   }
   else if(renderType == 3)
   {
      color = vec4(texture(albedo_specTexture,fragTexCoords).aaa,1.0);
   }
}