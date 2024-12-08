#version 410 core

in vec3 fragmentLocalPosition;
uniform samplerCube UISky;
out vec4 frag_colour;

void main () {
    frag_colour = texture(UISky, fragmentLocalPosition);
}