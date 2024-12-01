#version 410 core

layout(location = 0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float scale;  // New uniform for scaling

out vec3 fragmentLocalPosition;

void main () {
    // Remove translation from the view matrix by using only its rotation part
    mat4 view = mat4(mat3(viewMatrix));
    gl_Position = projectionMatrix * view * vec4(vp * scale, 1.0); // Apply scale
    
    fragmentLocalPosition = vp;
}