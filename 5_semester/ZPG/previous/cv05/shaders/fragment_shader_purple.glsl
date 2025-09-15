#version 330 core

in vec3 vertexColor;
out vec4 frag_colour;

void main()
{
    frag_colour = vec4(vertexColor * vec3(0.5, 0.0, 0.5), 1.0);
}