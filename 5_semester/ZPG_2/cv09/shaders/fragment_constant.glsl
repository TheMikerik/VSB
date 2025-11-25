#version 330 core

out vec4 frag_colour;

uniform bool isSelected;

void main()
{
    frag_colour = isSelected ? vec4(1.0, 0.0, 0.0, 1.0) : vec4(0.6, 0.6, 0.6, 1.0);
}