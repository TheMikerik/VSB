#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vertexColor;
out vec3 Normal;    // Normal vector in world space
out vec3 FragPos;   // Fragment position in world space

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    vertexColor = aNormal;
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal; // Transform normal to world space
}