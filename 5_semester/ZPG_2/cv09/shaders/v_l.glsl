#version 330 core

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 worldNormal;
out vec3 worldPosition;

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;

void main () {
    worldNormal = transpose(inverse(mat3(modelMatrix))) * vn;
    vec4 position = modelMatrix * vec4(vp, 1.0);
    worldPosition = position.xyz / position.w;
    gl_Position = projectionMatrix * viewMatrix * position;
}