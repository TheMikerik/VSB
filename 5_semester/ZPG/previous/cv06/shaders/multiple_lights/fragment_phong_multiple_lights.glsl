#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 frag_colour;

// Define a structure for point lights
struct PointLight {
    vec3 position;
    vec3 color;
};

// Maximum number of point lights
#define MAX_LIGHTS 10

// Uniform array of point lights
uniform int numLights; // Number of active lights
uniform PointLight pointLights[MAX_LIGHTS];

uniform vec3 viewPos;

void main()
{
    // Ambient properties
    float ambientStrength = 0.1;
    vec3 ambient = vec3(0.0);

    // Initialize diffuse and specular components
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    
    // Normalize the normal vector
    vec3 norm = normalize(Normal);
    
    // Calculate the view direction once
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Iterate over each light
    for(int i = 0; i < numLights; i++) {
        // Calculate ambient component for each light
        ambient += ambientStrength * pointLights[i].color;
        
        // Calculate light direction
        vec3 lightDir = normalize(pointLights[i].position - FragPos);
        
        // Diffuse shading
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * pointLights[i].color;
        
        // Specular shading
        float specularStrength = 0.5;
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        specular += specularStrength * spec * pointLights[i].color;
    }

    // Combine all components
    vec3 result = (ambient + diffuse + specular);
    
    // Apply object color (e.g., green)
    vec3 objectColor = vec3(0.0, 1.0, 0.0);
    frag_colour = vec4(result * objectColor, 1.0);
}