#version 330 core

layout(points) in;
layout(line_strip,max_vertices = 6) out;

in VS_OUT {
   vec3  worldPosition;
   mat3 TBN;
} gs_in[];

out vec3 fColor;

uniform mat4 V;
uniform mat4 P;
uniform float scale = 0.2;
void build_line(vec4 position, vec3 direction, mat3 TBN)
{
   mat4 VP = P*V;
   gl_Position = VP*position;
   EmitVertex();
   gl_Position = VP*(position + vec4(TBN*direction,0.0) * scale);
   EmitVertex();
   EndPrimitive();
}
void main(){

   fColor = vec3(0,0,1.0); // gs_in[0] since there's only one input vertex
   build_line(vec4(gs_in[0].worldPosition,1.0),vec3(0,0,1),gs_in[0].TBN);
   fColor = vec3(1.0,0,0); // gs_in[0] since there's only one input vertex
   build_line(vec4(gs_in[0].worldPosition,1.0),vec3(1,0,0),gs_in[0].TBN);
   fColor = vec3(0,1.0,0.0); // gs_in[0] since there's only one input vertex
   build_line(vec4(gs_in[0].worldPosition,1.0),vec3(0,1,0),gs_in[0].TBN);

  
}