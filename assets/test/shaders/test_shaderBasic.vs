#version 330 core
layout (location = 0) in vec2 position;

uniform int aInt;
uniform vec2 aVec2;
uniform mat3 aMat3;


void main()
{
   vec3 vec = vec3(position.x + aInt, position.y + aVec2.x, 1.0);
    gl_Position = vec4(aMat3*vec,1.0);
}