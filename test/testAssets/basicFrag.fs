#version 330 core
uniform vec3 debugColor;
out vec4 color;

void main()
{
    color = vec4(debugColor, 1.0f); // Set alle 4 vector values to 1.0f
}