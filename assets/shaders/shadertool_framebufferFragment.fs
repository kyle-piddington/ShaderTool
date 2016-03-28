#version 330 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec3 gTexcoords;

in vec3 fragPos;
in vec3 fragNor;
in vec2 fragTexCoords;

void main()
{
    // Store the fragment position vector in the first gbuffer texture
    gPosition = fragPos;
    // Also store the per-fragment normals into the gbuffer
    gNormal = normalize(fragNor);
    // Store the texture coordinates in the framebuffer.
    gTexcoords = vec3(fragTexCoords,0.0);
}