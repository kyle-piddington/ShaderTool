#version 330 core
uniform vec3 debugColor = vec3(0.0,1.0,0.0);
out vec4 color;
in vec3 fragNor;

void main()
{
    color = vec4(debugColor + 0.5f * normalize(fragNor) + 0.5f, 1.0f);
}