#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 frag_colour;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    float distance = length(lightPos - FragPos);

    float constant = 1.0;
    float linear = 0.09;
    float quadratic = 0.032;
    float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
    
    vec3 result = (ambient + diffuse + specular) * attenuation;
    frag_colour = vec4(result * vec3(0.0, 1.0, 0.0), 1.0);
}