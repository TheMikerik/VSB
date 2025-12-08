#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 viewPos;
uniform vec3 lightPos[30];
uniform vec3 lightColor[30];
uniform int  numLights;

uniform sampler2D texture_diffuse1;
uniform bool hasTexture;

uniform vec3  materialAmbient;
uniform vec3  materialDiffuse;
uniform vec3  materialSpecular;
uniform float materialShininess;

uniform bool isSelected;
uniform bool isEmissive;

uniform vec3 spotDir;
uniform vec3 spotLightPosition;

void main()
{
    vec3 norm    = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    const float constant  = 1.0;
    const float linear    = 0.18;
    const float quadratic = 0.19;

    float baseAmbientStrength = 0.1;
    vec3 baseAmbient = baseAmbientStrength * vec3(1.0);
    vec3 lighting = baseAmbient; 

    for (int i = 0; i < numLights; ++i) {
        vec3 lightDir = normalize(lightPos[i] - FragPos);

        vec3 ambient  = materialAmbient * lightColor[i];

        float diff    = max(dot(norm, lightDir), 0.0);
        vec3 diffuse  = materialDiffuse * diff * lightColor[i];

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec      = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
        vec3 specular   = materialSpecular * spec * lightColor[i];

        float distance   = length(lightPos[i] - FragPos);
        float attenuation= 1.0 / (constant + linear * distance + quadratic * distance * distance);

        lighting += (ambient + diffuse + specular) * attenuation;
    }

    vec3 texColor = hasTexture ? texture(texture_diffuse1, TexCoord).rgb : vec3(1.0);
    vec3 finalColor;
    
    if (isEmissive) {
        finalColor = texColor;
    } else {
        finalColor = lighting * texColor;
    }
    
    if (length(spotDir) > 0.01) {
        vec3 spotLightVector = normalize(spotLightPosition - FragPos);
        vec3 spotReflectVector = reflect(-spotLightVector, norm);
        
        float spotDiff = max(dot(norm, spotLightVector), 0.0);
        vec3 spotDiffuse = spotDiff * texColor;
        
        float spotSpec = pow(max(dot(spotReflectVector, viewDir), 0.0), materialShininess);
        vec3 spotSpecular = spotSpec * vec3(1.0);
        
        float spotAngle = dot(normalize(spotDir), -spotLightVector);
        float spotCutoff = 0.97;
        
        if (spotAngle > spotCutoff) {
            float spotIntensity = (spotAngle - spotCutoff) / (1.0 - spotCutoff);
            float spotDistance = length(spotLightPosition - FragPos);
            float spotAttenuation = 1.0 / (constant + linear * spotDistance + quadratic * spotDistance * spotDistance);

            finalColor += (spotDiffuse + spotSpecular) * spotIntensity * spotAttenuation;
        }
    }
    
    if (isSelected) {
        finalColor = mix(finalColor, vec3(1.0, 0.0, 0.0), 0.8);
    }
    
    FragColor = vec4(finalColor, 1.0);
}