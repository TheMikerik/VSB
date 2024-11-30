#version 330 core

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 worldNormal;
out vec3 worldPosition;
out vec2 TexCoord;

layout(location=0) in vec3 vp; // Vertex Position
layout(location=1) in vec3 vn; // Vertex Normal
layout(location=2) in vec2 vt; // Vertex Texture Coordinate

void main() {
    worldNormal = transpose(inverse(mat3(modelMatrix))) * vn;
    vec4 position = modelMatrix * vec4(vp, 1.0);
    worldPosition = position.xyz;
    TexCoord = vt;
    gl_Position = projectionMatrix * viewMatrix * position;
}