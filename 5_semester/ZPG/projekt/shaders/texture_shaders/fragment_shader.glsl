#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 viewPos;
uniform vec3 lightPos[30]; // Array of light positions
uniform vec3 lightColor[30]; // Array of light colors
uniform int numLights;

// Material properties
uniform sampler2D texture_diffuse1;
uniform bool hasTexture;

uniform vec3 materialAmbient;   // Ambient reflection coefficient
uniform vec3 materialDiffuse;   // Diffuse reflection coefficient
uniform vec3 materialSpecular;  // Specular reflection coefficient
uniform float materialShininess; // Shininess coefficient for specular highlight

void main()
{
    vec3 result = vec3(0.0);
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Constants for attenuation calculation
    float constant = 1.0;
    float linear = 0.18;
    float quadratic = 0.19;
 
    for (int i = 0; i < numLights; ++i) {
        // Ambient component
        vec3 ambient = materialAmbient * lightColor[i];
        
        // Diffuse component
        vec3 lightDir = normalize(lightPos[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = materialDiffuse * diff * lightColor[i];

        // Specular component
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
        vec3 specular = materialSpecular * spec * lightColor[i];

        // Attenuation
        float distance = length(lightPos[i] - FragPos);
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));
        
        // Combine results
        result += (ambient + diffuse + specular) * attenuation;
    }
    
    // Apply texture color if texture is available
    vec3 textureColor = hasTexture ? texture(texture_diffuse1, TexCoord).rgb : vec3(1.0);
    
    result *= textureColor;
    FragColor = vec4(result, 1.0);
}