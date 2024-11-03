// lambert_fragment_shader.glsl
#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 frag_colour;

// Light properties
uniform vec3 lightPos;
uniform vec3 lightColor;

// Camera position (optional for diffuse lighting, not needed for pure Lambert)
uniform vec3 viewPos;

void main()
{
    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Combine ambient and diffuse components
    vec3 result = (ambient + diffuse);
    frag_colour = vec4(result, 1.0);
}