#version 330 core

#define NUM_LIGHTS 10

in vec3 FragPos;
in vec3 Normal;

out vec4 frag_colour;

uniform vec3 lightPos[NUM_LIGHTS];
uniform vec3 lightColor[NUM_LIGHTS];

uniform vec3 viewPos;

void main()
{
    vec3 ambientTotal = vec3(0.0);
    vec3 diffuseTotal = vec3(0.0);
    vec3 specularTotal = vec3(0.0);
    
    float ambientStrength = 0.1;
    float specularStrength = 0.5;
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    for(int i = 0; i < NUM_LIGHTS; i++){
        vec3 lightDir = normalize(lightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

        ambientTotal += ambientStrength * lightColor[i];
        diffuseTotal += diff * lightColor[i];
        specularTotal += specularStrength * spec * lightColor[i];
    }

    vec3 result = ambientTotal + diffuseTotal + specularTotal;
    frag_colour = vec4(result, 1.0);
}