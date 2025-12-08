#version 330 core

in vec3 worldNormal;
in vec3 worldPosition;
uniform vec3 spotDir;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform bool isSelected;

out vec4 fragColor;

void main() {
    vec3 camVector = normalize(viewPos - worldPosition);
    vec3 lightVector = normalize(lightPos - worldPosition);
    vec3 norm = normalize(worldNormal);
    vec3 reflectVector = reflect(-lightVector, norm);

    vec3 ambientColor = vec3(0.15, 0.15, 0.15);
    vec3 diffuseColor = vec3(0.0, 1.0, 0.0);
    vec3 specularColor = vec3(1.0, 1.0, 1.0);

    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * ambientColor;

    float diff = max(dot(norm, lightVector), 0.0);
    vec3 diffuse = diff * diffuseColor;

    float specularStrength = 0.5;
    float spec = pow(max(dot(reflectVector, camVector), 0.0), 32);
    vec3 specular = specularStrength * spec * specularColor;

    float baseLighting = 0.1;
    const float constant  = 1.0;
    const float linear    = 0.18;
    const float quadratic = 0.19;

    float spot = dot(normalize(spotDir), -lightVector);
    if (spot < 0.97) {
        specular = vec3(0.0);
        diffuse *= baseLighting;
        spot = 0.0;
    } else {
        spot = (spot - 0.97) / (1.0 - 0.97);

        float spotDistance = length(lightPos - worldPosition);
        float spotAttenuation = 1.0 / (constant + linear * spotDistance + quadratic * spotDistance * spotDistance);
        spot *= spotAttenuation;
    }

    vec3 finalColor = ambient + (diffuse + specular) * max(spot, baseLighting);

    if (isSelected) {
        finalColor = mix(finalColor, vec3(1.0, 0.0, 0.0), 0.8);
    }
    
    fragColor = vec4(finalColor, 1.0);
}