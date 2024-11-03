// fragment_blinn.glsl
#version 330 core

in vec3 FragPos;  // Position of the fragment in world space
in vec3 Normal;   // Normal of the fragment in world space

out vec4 frag_colour; // Output fragment color

// Light properties
uniform vec3 lightPos;    // Position of the light source
uniform vec3 lightColor;  // Color/intensity of the light

// Camera properties
uniform vec3 viewPos;     // Position of the camera/viewer

// Hardcoded Material properties
const vec3 materialAmbient  = vec3(0.2, 0.2, 0.2);    // Ambient reflectivity
const vec3 materialDiffuse  = vec3(0.5, 0.5, 0.5);    // Diffuse reflectivity
const vec3 materialSpecular = vec3(1.0, 1.0, 1.0);    // Specular reflectivity
const float materialShininess = 32.0;                 // Shininess coefficient

void main()
{
    // Ambient component
    vec3 ambient = materialAmbient * lightColor;

    // Normalize the normal vector
    vec3 norm = normalize(Normal);
    
    // Calculate the light direction vector and normalize it
    vec3 lightDir = normalize(lightPos - FragPos);
    
    // Diffuse component using Lambert's cosine law
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = materialDiffuse * diff * lightColor;
    
    // View direction vector and normalize it
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Calculate the halfway vector between light direction and view direction
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    // Specular component using Blinn-Phong model
    float spec = pow(max(dot(norm, halfwayDir), 0.0), materialShininess);
    vec3 specular = materialSpecular * spec * lightColor;
    
    // Combine all lighting components
    vec3 result = ambient + diffuse + specular;
    frag_colour = vec4(result * vec3(0.0, 0.0, 1.0), 1.0);
}