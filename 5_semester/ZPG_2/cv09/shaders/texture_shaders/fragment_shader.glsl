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

void main()
{
    vec3 norm    = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    const float constant  = 1.0;
    const float linear    = 0.18;
    const float quadratic = 0.19;

    vec3 lighting = vec3(0.0);

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
    vec3 finalColor = lighting * texColor;
    
    if (isSelected) {
        finalColor = mix(finalColor, vec3(1.0, 0.0, 0.0), 0.8);
    }
    
    FragColor = vec4(finalColor, 1.0);
}