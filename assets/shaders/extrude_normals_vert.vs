#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out VS_OUT { 
   vec3 normal;
} vs_out;


uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


void main()
{
   //Create the output position
    gl_Position = P * V * M * vec4(position, 1.0f);
    //Normal is Transpose inverse of MV matrix
    mat3 normalMatrix = mat3(transpose(inverse(V * M)));
    //Set the normal in perspective space, since we are only displaying it
    vs_out.normal = normalize(vec3(P * vec4(normalMatrix * normal, 1.0)));
}
