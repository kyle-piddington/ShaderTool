#version 330 core
in vec3 fragPos;
in vec3 fragNor;
uniform vec3 fillColor;
uniform vec3 lineColor;
uniform float threshold;
out vec4 color;

void main()
{
   vec3 nor = normalize(fragNor);
   vec3 fragColor = vec3(fillColor);
   if(max (0.0, abs(dot(nor,normalize(fragPos)))) < threshold)
   {
      fragColor = lineColor;
   }
   color = vec4(fragColor, 1.0);
}