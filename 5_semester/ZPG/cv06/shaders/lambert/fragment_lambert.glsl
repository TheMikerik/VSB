// lambert_fragment_shader.glsl
#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 frag_colour;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 viewPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 result = (ambient + diffuse);
    frag_colour = vec4(result * vec3(1.0, 0.0, 0.0), 1.0);
}