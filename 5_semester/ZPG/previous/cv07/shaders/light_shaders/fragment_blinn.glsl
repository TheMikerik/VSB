#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 frag_colour;

uniform vec3 viewPos;
uniform vec3 lightPos[10];
uniform vec3 lightColor[10];
uniform int numLights;

// Material properties
const vec3 materialAmbient  = vec3(0.2);
const vec3 materialDiffuse  = vec3(0.5);
const vec3 materialSpecular = vec3(1.0);
const float materialShininess = 32.0;

void main()
{
    vec3 result = vec3(0.0);
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    float constant = 1.0;
    float linear = 0.045;
    float quadratic = 0.0075;

    for (int i = 0; i < numLights; ++i) {
        // Ambient
        vec3 ambient = materialAmbient * lightColor[i];
        
        // Diffuse
        vec3 lightDir = normalize(lightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = materialDiffuse * diff * lightColor[i];
        
        // Specular (Blinn-Phong)
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
        vec3 specular = materialSpecular * spec * lightColor[i];
        
        // Attenuation
        float distance = length(lightPos[i] - FragPos);
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
        
        result += (ambient + diffuse + specular) * attenuation;
    }
    
    frag_colour = vec4(result * vec3(0.0, 0.0, 1.0), 1.0);
}