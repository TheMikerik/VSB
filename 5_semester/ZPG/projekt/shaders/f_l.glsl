#version 330 core

in vec3 worldNormal;
in vec3 worldPosition;
uniform vec3 spotDir;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 fragColor;

void main () {
    vec3 camVector = normalize(viewPos - worldPosition);
    vec3 lightVector = normalize(lightPos - worldPosition);
    vec3 norm = normalize(worldNormal);
    vec3 reflectVector = reflect(-lightVector, norm);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(0.385, 0.647, 0.812);

    float diff = max(dot(norm, lightVector), 0.0);
    vec3 diffuse = diff * vec3(0.385, 0.647, 0.812);

    float specularStrength = 0.5;
    float spec = pow(max(dot(reflectVector, camVector), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(0.385, 0.647, 0.812);

    float spot = dot(normalize(spotDir), -lightVector);
    if (spot < 0.99) {
        specular = vec3(0.0);
        diffuse = vec3(0.0);
    }
    spot = (spot - 0.99) / (1.0 - 0.99);

    fragColor = vec4(ambient + (diffuse + specular) * spot, 1.0);
}