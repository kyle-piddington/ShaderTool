#version 330 core

in vec3 fragCol;
out vec4 color;

void main(){
   color = vec4(fragCol, 1.0);
}