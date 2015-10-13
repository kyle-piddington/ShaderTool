#version 330 core
layout (location = 0) out vec4 gPositionDepth;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec3 fragPos;
in vec3 fragNor;


const float NEAR = 0.1;
const float FAR = 50.0;

/**
 * Linearize the exponential depth curve back to a 
 * linear mapping.
 */
float linearizeDepth(float depth)
{
   float z = depth * 2.0 - 1.0; // Back to NDC 
   return (2.0 * NEAR * FAR) / (FAR + NEAR - z * (FAR - NEAR));
}

void main()
{
   gPositionDepth.xyz = fragPos;
    // And store linear depth into gPositionDepth's alpha component
   gPositionDepth.a = linearizeDepth(gl_FragCoord.z); 
    // Also store the per-fragment normals into the gbuffer
   gNormal = normalize(fragNor);
    // And the diffuse per-fragment color
   gAlbedoSpec.rgb = vec3(0.95);
   gAlbedoSpec.a = 1.0;
}

