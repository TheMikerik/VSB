#version 410 core

layout(location = 0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float scale;

out vec3 fragmentLocalPosition;

void main () {
    mat4 view = mat4(mat3(viewMatrix));
    gl_Position = projectionMatrix * view * vec4(vp * scale, 1.0);
    
    fragmentLocalPosition = vp;
}