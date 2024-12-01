#version 330 core
layout(location = 0) in vec3 aPos;       // Position
layout(location = 1) in vec3 aNormal;    // Normal
layout(location = 2) in vec2 aTexCoord;  // Texture Coordinate

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;  
    TexCoord = aTexCoord;
    
    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
}