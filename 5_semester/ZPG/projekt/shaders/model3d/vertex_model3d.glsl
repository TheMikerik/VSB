#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords; // Add texture coordinate input

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords; // Pass texture coordinates to fragment shader

void main()
{
    // Calculate the position of the vertex in world space
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    
    // Calculate the normal in world space and normalize it
    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
    
    // Pass the texture coordinates to the fragment shader
    TexCoords = aTexCoords;
    
    // Calculate the final position of the vertex in clip space
    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}