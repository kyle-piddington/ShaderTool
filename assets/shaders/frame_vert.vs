#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec3 tangent;

out VS_OUT {
   vec3  worldPosition;
   mat3 TBN;
} vs_out;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
void main()
{
   vs_out.worldPosition = vec3(M*vec4(position,1.0));
   vec3 T = normalize(vec3(M * vec4(tangent, 0.0)));
   vec3 N = normalize(vec3(M * vec4(normal, 0.0)));
   // re-orthogonalize T with respect to NULL
   T = normalize(T - dot(T, N) * N);
   vec3 B = cross(T,N);

   vs_out.TBN = mat3(T, B, N);

}