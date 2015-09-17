#version 330 core
in vec3 fragPosition;
in vec3 fragNor;
out vec4 color;

uniform vec3 cameraPos;
uniform samplerCube skybox;
void main()
{
   vec3 I = normalize(fragPosition - cameraPos);
   vec3 R = reflect(I,normalize(fragNor));
   color = texture(skybox,R);

}
