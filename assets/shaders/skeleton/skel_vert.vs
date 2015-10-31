#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

out vec2 fragTexCoords;
out vec3 fragNor;
out vec3 fragPos;

const int MAX_BONES = 100;

uniform mat4 V;
uniform mat4 M;
uniform mat4 P;
uniform mat4 gBones[MAX_BONES];
uniform mat4 gBinds[MAX_BONES];


void main()
{
    mat4 BoneTransform = gBones[BoneIDs[0]] * gBinds[BoneIDs[0]] * Weights[0];
    BoneTransform +=     gBones[BoneIDs[1]] * gBinds[BoneIDs[1]] * Weights[1];
    BoneTransform +=     gBones[BoneIDs[2]] * gBinds[BoneIDs[2]] * Weights[2];
    BoneTransform +=     gBones[BoneIDs[3]] * gBinds[BoneIDs[3]] * Weights[3];

    vec4 PosL = M*BoneTransform * vec4(Position, 1.0);
    gl_Position = P* V * PosL;
    fragTexCoords = TexCoord;
    vec4 NormalL = BoneTransform * vec4(Normal, 0.0);
    fragNor = (NormalL).xyz;
    fragPos = (PosL).xyz;
}