#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    // Transform the vertex position to world space
    vec4 worldPos = modelMatrix * vec4(aPos, 1.0);
    FragPos = vec3(worldPos);

    // Transform the normal to world space and normalize
    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
    Normal = normalize(Normal);

    // Calculate the final vertex position in clip space
    gl_Position = projectionMatrix * viewMatrix * worldPos;
}