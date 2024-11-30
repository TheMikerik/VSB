#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 frag_colour;

uniform vec3 viewPos;
uniform vec3 lightPos[10];
uniform vec3 lightColor[10];
uniform int numLights;

// Material properties
uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShininess;

void main()
{
    vec3 result = vec3(0.0);
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    float constant = 1.0;
    float linear = 0.045;
    float quadratic = 0.0075;

    for (int i = 0; i < numLights; ++i) {
        vec3 ambient = materialAmbient * lightColor[i];
        
        vec3 lightDir = normalize(lightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = materialDiffuse * diff * lightColor[i];
        
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
        vec3 specular = materialSpecular * spec * lightColor[i];
        
        float distance = length(lightPos[i] - FragPos);
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
        
        result += (ambient + diffuse + specular) * attenuation;
    }
    
    frag_colour = vec4(result * vec3(0.0, 1.0, 0.0), 1.0);
}