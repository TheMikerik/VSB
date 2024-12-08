#version 330 core

in vec3 worldNormal;
in vec3 worldPosition;
in vec2 TexCoord;

uniform vec3 spotDir;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;
uniform bool hasTexture;

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShininess;

out vec4 fragColor;

void main() {
    vec3 camVector = normalize(viewPos - worldPosition);
    vec3 lightVector = normalize(lightPos - worldPosition);
    vec3 norm = normalize(worldNormal);
    vec3 reflectVector = reflect(-lightVector, norm);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * materialAmbient;

    float diff = max(dot(norm, lightVector), 0.0);
    vec3 diffuse = materialDiffuse * diff;

    float specularStrength = 0.5;
    float spec = pow(max(dot(reflectVector, camVector), 0.0), materialShininess);
    vec3 specular = specularStrength * spec * materialSpecular;

    float spot = dot(normalize(spotDir), -lightVector);
    if (spot < 0.99) {
        specular = vec3(0.0);
        diffuse = vec3(0.0);
    }
    spot = (spot - 0.99) / (1.0 - 0.99);

    vec3 textureColor = hasTexture ? texture(texture_diffuse1, TexCoord).rgb : vec3(1.0);

    vec3 finalColor = (ambient + (diffuse + specular) * spot) * textureColor;
    fragColor = vec4(finalColor, 1.0);
}