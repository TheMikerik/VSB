// blinn_vertex_shader.glsl
#version 330 core

layout (location = 0) in vec3 aPos;    // Vertex position
layout (location = 1) in vec3 aNormal; // Vertex normal

uniform mat4 modelMatrix;      // Model transformation matrix
uniform mat4 viewMatrix;       // View (camera) transformation matrix
uniform mat4 projectionMatrix; // Projection matrix

out vec3 FragPos;  // Position of the fragment in world space
out vec3 Normal;   // Normal of the fragment in world space

void main()
{
    // Transform the vertex position to world space
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    
    // Transform and normalize the normal vector to world space
    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
    
    // Calculate the final vertex position in clip space
    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}