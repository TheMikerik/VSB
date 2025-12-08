#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 frag_colour;

uniform vec3 lightPos[30];
uniform vec3 lightColor[30];
uniform int numLights;
uniform vec3 viewPos;
uniform bool isSelected;

void main()
{
    vec3 result = vec3(0.0);
    vec3 norm = normalize(Normal);

    float constant = 1.0;
    float linear = 0.18;
    float quadratic = 0.19;

    for (int i = 0; i < numLights; ++i) {
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor[i];
        
        vec3 lightDir = normalize(lightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor[i];
        
        float distance = length(lightPos[i] - FragPos);
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
        
        result += (ambient + diffuse) * attenuation;
    }
    
    vec3 finalColor = result * vec3(1.0, 0.0, 0.0);
    
    if (isSelected) {
        finalColor = mix(finalColor, vec3(1.0, 0.0, 0.0), 0.8);
    }
    
    frag_colour = vec4(finalColor, 1.0);
}