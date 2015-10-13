#version 330 core
#define KERN_SIZE 64
#define RADIUS 1.0
#define POWER 2
layout (location = 0) out float ssaoMap;

in vec2 fragTexCoords;


uniform sampler2D gPositionDepth;
uniform sampler2D gNormal;
uniform sampler2D noiseTexture;

uniform vec3 samples[KERN_SIZE];
uniform mat4 P;

// tile noise texture over screen based on screen dimensions divided by noise size
const vec2 noiseScale = vec2(800.0/4.0, 600.0/4.0); // screen = 800x600




void main()
{
   vec3 fragPos = texture(gPositionDepth,fragTexCoords).xyz;
   vec3 normal = texture(gNormal,fragTexCoords).rgb;
   vec3 randomVec = texture(noiseTexture,fragTexCoords * noiseScale).xyz;
   //Create a TBN basis with the normal, a random tangent (orthonormalized).
   vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
   vec3 biTangent = cross(normal,tangent);
   mat3 TBN = mat3(tangent,biTangent,normal);

   float occlusion = 0.0;
   for(int i = 0; i < KERN_SIZE; i++)
   {
      vec3 sample = TBN * samples[i]; //Tangent space to view space
      sample += fragPos + sample * RADIUS;

      vec4 offset = vec4(sample, 1.0);
      offset = P * offset; // from view to clip-space
      offset.xyz /= offset.w; // perspective divide
      offset.xyz = offset.xyz * 0.5 + 0.5; // transform from -1 --> 1 to range 0.0 --> 1.0  
      //Sample the depth from the position
      float sampleDepth = -texture(gPositionDepth, offset.xy).w;
      //Add to occlusion if sample is 'inside' a wall
      
      //only add occlusion if sample and z are within RADIUS
      float rangeCheck = smoothstep(0.0, 1.0, RADIUS / abs(fragPos.z - sampleDepth));
      occlusion += (sampleDepth >= sample.z ? 1.0 : 0.0) * rangeCheck;          
   }
   occlusion = 1 - (occlusion/KERN_SIZE);
   ssaoMap = pow(occlusion,POWER);

}

